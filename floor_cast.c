/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 04:35:24 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/01 17:05:51 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			init_floor_cast(t_raycast *r, t_floorcast *f)
{
	if (r->side == 0 && r->ray_dir.x > 0)
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

static void			loop_floor_cast(t_env *e, t_raycast *r,
	t_floorcast *f, int y)
{
	f->current_dist = r->h / (2.0 * y - r->h);
	f->weight = (f->current_dist - f->dist_player) /
		(f->dist_wall - f->dist_player);
	f->current_floor.x = f->weight * f->floor_wall.x +
		(1.0 - f->weight) * e->pos.x;
	f->current_floor.y = f->weight * f->floor_wall.y +
		(1.0 - f->weight) * e->pos.y;
	f->floor_tex_x = (int)(f->current_floor.x * TEX_WIDTH) % TEX_WIDTH;
	f->floor_tex_y = (int)(f->current_floor.y * TEX_HEIGHT) % TEX_HEIGHT;
}

static SDL_Surface	*get_ceiling_color(t_floorcast *f, t_env *e)
{
	if (f->current_floor.x > 22 && f->current_floor.x < 32 &&
		f->current_floor.y > 1 && f->current_floor.y < 13)
		return (e->wall_bluestone);
	else
		return (e->wall_wood);
}

static void			color_floor_cast(t_floorcast *f, t_env *e, t_raycast *r)
{
	t_rgba			color;
	SDL_Surface		*selected_surface;
	int				checker;
	int				no_floor;

	no_floor = 0;
	if ((selected_surface = get_ceiling_color(f, e)) == NULL)
	{
		no_floor = 1;
		selected_surface = e->wall_wood;
	}
	if (e->player.life == 0)
		selected_surface = e->game_over;
	checker = ((int)f->current_floor.x + (int)f->current_floor.y) % 2;
	if (checker == 0)
		color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH *
			f->floor_tex_y + f->floor_tex_x];
	else
		color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH *
			f->floor_tex_x + f->floor_tex_y];
	operate_rgba(&color, '/', (5 / f->shadow));
	e->img_buffer[WIN_X * f->y + f->x] = COLOR;
	operate_rgba(&color, '/', (4 / f->shadow));
	if (!no_floor)
		e->img_buffer[WIN_X * (r->h - f->y) + f->x] = COLOR;
}

void				floor_cast(t_env *e, t_raycast *r, int x)
{
	t_floorcast		f;
	int				y;

	init_floor_cast(r, &f);
	if (r->draw_end < 0)
		r->draw_end = r->h;
	y = r->draw_end;
	while (++y < r->h)
	{
		loop_floor_cast(e, r, &f, y);
		f.x = x;
		f.y = y;
		f.shadow = (e->shadows[(int)f.current_floor.x][(int)f.current_floor.y]);
		color_floor_cast(&f, e, r);
	}
}
