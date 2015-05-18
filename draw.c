/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:14:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/18 08:35:35 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

Uint32 create_color(int r, int g, int b)
{
	return (((r << 8)+ g) << 8)+ b;
}

void			operate_rgba(t_rgba *c, char op, int value)
{
	if (op == '/')
	{
		c->r /= value;
		c->g /= value;
		c->b /= value;
	}
	else if (op == '+')
	{
		c->r += value;
		c->g += value;
		c->b += value;
	}
}

void			create_rgb(t_rgba *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

static void			init_floor_cast(t_raycast *r, t_floorcast *f)
{
	if(r->side == 0 && r->ray_dir.x > 0)
	{
		f->floor_wall.x = r->map_x;
		f->floor_wall.y = r->map_y + r->wall_x;
	}
	else if (r->side == 0 && r->ray_dir.x < 0)
	{
		f->floor_wall.x = r->map_x + 1.0;
		f->floor_wall.y = r->map_y + r->wall_x;
	}
	else if (r->side == 1 && r->ray_dir.y > 0)
	{
		f->floor_wall.x = r->map_x + r->wall_x;
		f->floor_wall.y = r->map_y;
	}
	else
	{
		f->floor_wall.x = r->map_x + r->wall_x;
		f->floor_wall.y = r->map_y + 1.0;
	} 
	f->dist_wall = r->perp_wall_dist;
	f->dist_player = 0.0;
}

void				floor_cast(t_env *e, t_raycast *r, int x)
{
	t_floorcast		f;
	t_rgba			color;
	int				checker;
	SDL_Surface		*selected_surface;
	int				y;

	init_floor_cast(r, &f);
	if (r->draw_end < 0)
		r->draw_end = r->h;
	y = r->draw_end;
	while (++y < r->h)
	{
		f.current_dist = r->h / (2.0 * y - r->h); //you could make a small lookup table for this instead
		f.weight = (f.current_dist - f.dist_player) / (f.dist_wall - f.dist_player);
		f.current_floor.x = f.weight * f.floor_wall.x + (1.0 - f.weight) * e->pos.x;
		f.current_floor.y = f.weight * f.floor_wall.y + (1.0 - f.weight) * e->pos.y;
		f.floor_tex_x = (int)(f.current_floor.x * TEX_WIDTH) % TEX_WIDTH;
		f.floor_tex_y = (int)(f.current_floor.y * TEX_HEIGHT) % TEX_HEIGHT;
		selected_surface = e->wall_wood;
		checker = ((int)f.current_floor.x + (int)f.current_floor.y) % 2;
		if(checker == 0)
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * f.floor_tex_y + f.floor_tex_x];
		else
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * f.floor_tex_x + f.floor_tex_y];
		e->img_buffer[WIN_X * y + x] = create_color(color.b, color.g, color.r);
		e->img_buffer[WIN_X * (r->h - y) + x] = create_color(color.b, color.g, color.r);
	}
}

static void	init_ray_cast(t_env *e, t_raycast *r, int x)
{
	r->camera_x = 2 * x / (double) (r->w) - 1;
	r->ray_pos.x = e->pos.x;
	r->ray_pos.y = e->pos.y;
	r->ray_dir.x = e->dir.x + e->plane.x*r->camera_x;
	r->ray_dir.y = e->dir.y + e->plane.y*r->camera_x;
	r->map_x = (int)(r->ray_pos.x);
	r->map_y = (int)(r->ray_pos.y);
	r->delta_dist.x = sqrt(1 + (r->ray_dir.y * r->ray_dir.y) / (r->ray_dir.x * r->ray_dir.x));
	r->delta_dist.y = sqrt(1 + (r->ray_dir.x * r->ray_dir.x) / (r->ray_dir.y * r->ray_dir.y));
	if (r->ray_dir.x < 0)
	{
		r->step_x = -1;
		r->side_dist.x = (r->ray_pos.x - r->map_x) * r->delta_dist.x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist.x = (r->map_x + 1.0 - r->ray_pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step_y = -1;
		r->side_dist.y = (r->ray_pos.y - r->map_y) * r->delta_dist.y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist.y = (r->map_y + 1.0 - r->ray_pos.y) * r->delta_dist.y;
	}
}

static int	check_collision(t_env *e, t_raycast *r)
{
	if (e->level[r->map_x][r->map_y] > 0)
		return (1);
	else
		return (0);
}

void		draw(t_env *e)
{
	int			x;
	int			hit;
	int			wall_type;
	t_rgba		color;
	t_raycast	r;
	SDL_Surface *selected_surface;

	x = -1;
	r.h = WIN_Y;
	r.w = WIN_X;
	while (++x < r.w)
	{
		init_ray_cast(e, &r, x);
		hit = 0;
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (r.side_dist.x < r.side_dist.y)
			{
				r.side_dist.x += r.delta_dist.x;
				r.map_x += r.step_x;
				r.side = 0;
			}
			else
			{
				r.side_dist.y += r.delta_dist.y;
				r.map_y += r.step_y;
				r.side = 1;
			}
			hit = check_collision(e, &r);
		}
		wall_type = e->level[r.map_x][r.map_y];
		if (wall_type == 1)
			selected_surface = e->wall_greystone;
		else if (wall_type == 2)
			selected_surface = e->wall_colorstone;
		else if (wall_type == 3)
			selected_surface = e->wall_wood;
		else if (wall_type == 4)
			selected_surface = e->wall_bluestone;
		else if (wall_type == 5)
			selected_surface = e->wall_bluestone_jail;
		else if (wall_type == 6)
			selected_surface = e->wall_wood_paint;
		if (r.side == 0)
			r.perp_wall_dist = fabs((r.map_x - r.ray_pos.x + (1 - r.step_x) / 2) / r.ray_dir.x);
		else
			r.perp_wall_dist = fabs((r.map_y - r.ray_pos.y + (1 - r.step_y) / 2) / r.ray_dir.y);
		int lineHeight = abs((int)(r.h / r.perp_wall_dist));
		r.draw_start = -lineHeight / 2 + r.h / 2;
		if(r.draw_start < 0)
			r.draw_start = 0;
		r.draw_end = lineHeight / 2 + r.h / 2;
		if(r.draw_end >= r.h)
			r.draw_end = r.h - 1;
		if (r.side == 1)
			r.wall_x = r.ray_pos.x + ((r.map_y - r.ray_pos.y + (1 - r.step_y) / 2)
				/ r.ray_dir.y) * r.ray_dir.x;
		else
			r.wall_x = r.ray_pos.y + ((r.map_x - r.ray_pos.x + (1 - r.step_x) / 2)
				/ r.ray_dir.x) * r.ray_dir.y;
		r.wall_x -= floor((r.wall_x));
		int texX = (int)(r.wall_x * (double)(TEX_WIDTH));
		if(r.side == 0 && r.ray_dir.x > 0)
			texX = TEX_WIDTH - texX - 1;
		if(r.side == 1 && r.ray_dir.y < 0)
			texX = TEX_WIDTH - texX - 1;
		for(int y = r.draw_start; y < r.draw_end; y++)
		{
			int d = y * 256 - r.h * 128 + lineHeight * 128;  //256 and 128 factors to avoid doubles
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * texY + texX];
			if(r.side == 1)
			{
				color.r = (color.r >> 1) & 8355711;
				color.g = (color.g >> 1) & 8355711;
				color.b = (color.b >> 1) & 8355711;
			}
			e->img_buffer[WIN_X * y + x] = create_color(color.b, color.g, color.r);
		}
		floor_cast(e, &r, x);
		r.z_buffer[x] = r.perp_wall_dist;
	}
	sprite_cast(e, &r);
}
