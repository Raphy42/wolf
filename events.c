/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 03:07:27 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/12 21:57:19 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

int					event(t_env *e)
{
	const double	rotation_speed = e->frame_time * 3.0;
	const double	move_speed = e->frame_time * 5.0;

	SDL_Delay(5);
	if (e->event.key.keysym.sym == 27)
	{
		SDL_DestroyWindow(e->window);
		SDL_DestroyRenderer(e->render);
		SDL_Quit();
		exit(EXIT_SUCCESS);
	}
	if (e->event.key.keysym.sym == SDLK_UP)
	{
		if (e->level[(int)(e->pos.x + e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x += e->dir.x * move_speed;
		if (e->level[(int)e->pos.x][(int)(e->pos.y + e->dir.y * move_speed)] == 0)
			e->pos.y += e->dir.y * move_speed;
	}
	if (e->event.key.keysym.sym == SDLK_DOWN)
	{
		if (e->level[(int)(e->pos.x + e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x -= e->dir.x * move_speed;
		if (e->level[(int)e->pos.x][(int)(e->pos.y + e->dir.y * move_speed)] == 0)
			e->pos.y -= e->dir.y * move_speed;
	}
	if (e->event.key.keysym.sym == SDLK_RIGHT)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(-rotation_speed) - e->dir.y * sin(-rotation_speed);
		e->dir.y = e->old_dir_x * sin(-rotation_speed) + e->dir.y * cos(-rotation_speed);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(-rotation_speed) - e->plane.y * sin(-rotation_speed);
		e->plane.y = e->old_plane_x * sin(-rotation_speed) + e->plane.y * cos(-rotation_speed);
	}
	if (e->event.key.keysym.sym == SDLK_LEFT)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(rotation_speed) - e->dir.y * sin(rotation_speed);
		e->dir.y = e->old_dir_x * sin(rotation_speed) + e->dir.y * cos(rotation_speed);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(rotation_speed) - e->plane.y * sin(rotation_speed);
		e->plane.y = e->old_plane_x * sin(rotation_speed) + e->plane.y * cos(rotation_speed);
	}
	return (1);
}