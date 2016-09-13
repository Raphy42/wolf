/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:14:44 by rdantzer          #+#    #+#             */
/*   Updated: 2016/09/13 03:12:13 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

static int				check_collision(t_env *e, t_raycast *r)
{
	if (e->level[r->map_x][r->map_y] > 0)
		return (1);
	else
		return (0);
}

SDL_Surface				*select_wall_type(int wall_type, t_env *e)
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

static void				ray_cast_collision(t_env *e, t_raycast *r)
{
	int					hit;

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

static void				ray_cast_draw(int x, t_raycast *r, t_env *e,
	SDL_Surface *sel)
{
	int					y;
	t_rgba				color;

	y = r->draw_start - 1;
	while (++y < r->draw_end)
	{
		r->d = y * 256 - r->h * 128 + r->line_height * 128;
		r->tex_y = ((r->d * TEX_HEIGHT) / r->line_height) / 256;
		color = ((t_rgba *)sel->pixels)[TEX_WIDTH * r->tex_y + r->tex_x];
		operate_rgba(&color, '/', r->shadow);
		e->img_buffer[WIN_X * y + x] = create_color(color.b, color.g, color.r);
	}
}

void					draw(t_env *e)
{
	int					x;
	t_raycast			r;
	SDL_Surface			*selected_surface;

	x = -1;
	r.h = WIN_RAY_Y;
	r.w = WIN_X;
	while (++x < r.w)
	{
		init_ray_cast(e, &r, x);
		ray_cast_collision(e, &r);
		ray_cast(e, &r);
		selected_surface = select_wall_type(e->level[r.map_x][r.map_y], e);
		ray_cast_draw(x, &r, e, selected_surface);
		floor_cast(e, &r, x);
		r.z_buffer[x] = r.perp_wall_dist;
	}
	sprite_cast(e, &r);
}
