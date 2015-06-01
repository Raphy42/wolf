/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 11:26:04 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/30 19:41:00 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		init_ray_cast_step(t_raycast *r)
{
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

void			init_ray_cast(t_env *e, t_raycast *r, int x)
{
	r->camera_x = 2 * x / (double) (r->w) - 1;
	r->ray_pos.x = e->pos.x;
	r->ray_pos.y = e->pos.y;
	r->ray_dir.x = e->dir.x + e->plane.x*r->camera_x;
	r->ray_dir.y = e->dir.y + e->plane.y*r->camera_x;
	r->map_x = (int)(r->ray_pos.x);
	r->map_y = (int)(r->ray_pos.y);
	r->delta_dist.x = sqrt(1 + (r->ray_dir.y * r->ray_dir.y) /
		(r->ray_dir.x * r->ray_dir.x));
	r->delta_dist.y = sqrt(1 + (r->ray_dir.x * r->ray_dir.x) /
		(r->ray_dir.y * r->ray_dir.y));
	init_ray_cast_step(r);
}

static void		ray_cast_wall_dist(t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = fabs((r->map_x - r->ray_pos.x +
			(1 - r->step_x) / 2) / r->ray_dir.x);
	else
		r->perp_wall_dist = fabs((r->map_y - r->ray_pos.y +
			(1 - r->step_y) / 2) / r->ray_dir.y);
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
}

void			ray_cast(t_env *e, t_raycast *r)
{
	ray_cast_wall_dist(r);
	r->wall_x -= floor((r->wall_x));
	r->tex_x = (int)(r->wall_x * (double)(TEX_WIDTH));
	if(r->side == 0 && r->ray_dir.x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if(r->side == 1 && r->ray_dir.y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	r->shadow = 5 / (e->shadows[(int)r->map_x][(int)r->map_y] + 1);
}