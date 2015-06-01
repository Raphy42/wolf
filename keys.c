/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 09:31:40 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/29 09:57:22 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void				move_keys(t_env *e)
{
	const double		move_speed = e->frame_time * 5.0;

	if (e->key.up)
	{

		if (L[(int)(e->pos.x + e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x += e->dir.x * move_speed;
		if (L[(int)e->pos.x][(int)(e->pos.y + e->dir.y * move_speed)] == 0)
			e->pos.y += e->dir.y * move_speed;
	}
	if (e->key.down)
	{
		if (L[(int)(e->pos.x - e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x -= e->dir.x * move_speed;
		if (L[(int)e->pos.x][(int)(e->pos.y - e->dir.y * move_speed)] == 0)
			e->pos.y -= e->dir.y * move_speed;
	}
}

static void				rotate_keys(t_env *e)
{
	const double		rotation_speed = e->frame_time * 1.5;

	if (e->key.right)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(-ROT) - e->dir.y * sin(-ROT);
		e->dir.y = e->old_dir_x * sin(-ROT) + e->dir.y * cos(-ROT);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(-ROT) - e->plane.y * sin(-ROT);
		e->plane.y = e->old_plane_x * sin(-ROT) + e->plane.y * cos(-ROT);
	}
	if (e->key.left)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(ROT) - e->dir.y * sin(ROT);
		e->dir.y = e->old_dir_x * sin(ROT) + e->dir.y * cos(ROT);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(ROT) - e->plane.y * sin(ROT);
		e->plane.y = e->old_plane_x * sin(ROT) + e->plane.y * cos(ROT);
	}
}

void					run_event(t_env *e)
{
	move_keys(e);
	rotate_keys(e);
	check_prop_collide(e);
}
