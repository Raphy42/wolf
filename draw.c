/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:14:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/28 15:14:10 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

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

static SDL_Surface	*select_wall_type(int wall_type, t_env *e)
{
	if (e->player.life == 0)
		return (e->game_over);
	else if (wall_type == 1)
		return (e->wall_greystone);
	else if (wall_type == 2)
		return (e->wall_colorstone);
	else if (wall_type == 3)
		return (e->wall_wood);
	else if (wall_type == 4)
		return (e->wall_bluestone);
	else if (wall_type == 5)
		return (e->wall_bluestone_jail);
	else if (wall_type == 6)
		return (e->wall_wood_paint);
	else
		return (NULL);
}

static void		ray_cast(t_env *e, t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = fabs((r->map_x - r->ray_pos.x + (1 - r->step_x) / 2) / r->ray_dir.x);
	else
		r->perp_wall_dist = fabs((r->map_y - r->ray_pos.y + (1 - r->step_y) / 2) / r->ray_dir.y);
	r->line_height = abs((int)(r->h / r->perp_wall_dist));
	r->draw_start = -r->line_height / 2 + r->h / 2;
	if(r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + r->h / 2;
	if(r->draw_end >= r->h)
		r->draw_end = r->h - 1;
	if (r->side == 1)
		r->wall_x = r->ray_pos.x + ((r->map_y - r->ray_pos.y + (1 - r->step_y) / 2)
			/ r->ray_dir.y) * r->ray_dir.x;
	else
		r->wall_x = r->ray_pos.y + ((r->map_x - r->ray_pos.x + (1 - r->step_x) / 2)
			/ r->ray_dir.x) * r->ray_dir.y;
	r->wall_x -= floor((r->wall_x));
	r->tex_x = (int)(r->wall_x * (double)(TEX_WIDTH));
	if(r->side == 0 && r->ray_dir.x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if(r->side == 1 && r->ray_dir.y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	r->shadow = 5 / (e->shadows[(int)r->map_x][(int)r->map_y] + 1);
}

static void		ray_cast_collision(t_env *e, t_raycast *r)
{
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		hit = check_collision(e, r);
	}
}

void			draw(t_env *e)
{
	int			x;
	t_rgba		color;
	t_raycast	r;
	SDL_Surface *selected_surface;

	x = -1;
	r.h = WIN_RAY_Y;
	r.w = WIN_X;
	while (++x < r.w)
	{
		init_ray_cast(e, &r, x);
		ray_cast_collision(e, &r);
		ray_cast(e, &r);
		selected_surface = select_wall_type(e->level[r.map_x][r.map_y], e);
		for(int y = r.draw_start; y < r.draw_end; y++)
		{
			r.d = y * 256 - r.h * 128 + r.line_height * 128;  //256 and 128 factors to avoid doubles
			r.tex_y = ((r.d * TEX_HEIGHT) / r.line_height) / 256;
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * r.tex_y + r.tex_x];
			operate_rgba(&color, '/', r.shadow);
			e->img_buffer[WIN_X * y + x] = create_color(color.b, color.g, color.r);
		}
		floor_cast(e, &r, x);
		r.z_buffer[x] = r.perp_wall_dist;
	}
	sprite_cast(e, &r);
}
