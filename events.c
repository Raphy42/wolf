/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 03:07:27 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/22 06:14:10 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "wolf.h"
#include "libft.h"

static void		kill_all(t_env *e)
{
	SDL_DestroyWindow(e->window);
	SDL_DestroyRenderer(e->render);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void			event(t_env *e)
{
	if (e->player.hit)
		e->player.hit = 0;
	if (e->player.health <= 0 && e->player.life > 0)
	{
		e->player.life--;
		e->player.health = 100;
		e->pos.x = DEFAULT_POS_X;
		e->pos.y = DEFAULT_POS_Y;
	}
	if (e->player.life == 0)
	{
		e->player.hit = 1;
		e->player.health = 0;
		if (KEY != 27)
			return ;
	}
    if (e->event.type == SDL_KEYDOWN)
    {
        if (KEY == 27)
            kill_all(e);
        else if (KEY == SDLK_LEFT)
            e->key.left = 1;
        else if (KEY == SDLK_RIGHT)
            e->key.right= 1;
        else if (KEY == SDLK_UP)
            e->key.up = 1;
        else if (KEY == SDLK_DOWN)
            e->key.down = 1;
        else if (KEY == SDLK_TAB)
        	e->player.selected_weapon++;
        else if (KEY == SDLK_x && e->player.weapon_state <= 5)
        {
        	e->player.weapon_state = (6 - e->player.selected_weapon) * 5;
        	add_new_sprite(&e->sprite, create_new_sprite(e, e->pos.x, e->pos.y, PARTICULE_BULLET));
		}
		return ;
    }
    else if (e->event.type == SDL_KEYUP)
    {
        if (KEY == SDLK_LEFT)
            e->key.left = 0;
        else if (KEY == SDLK_RIGHT)
            e->key.right= 0;
        else if (KEY == SDLK_UP)
            e->key.up = 0;
        else if (KEY == SDLK_DOWN)
            e->key.down = 0;
    }
}

void				run_event(t_env *e)
{
	const double		rotation_speed = e->frame_time * 1.5;
	const double		move_speed = e->frame_time * 5.0;

	if (e->key.up)
	{

		if (e->level[(int)(e->pos.x + e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x += e->dir.x * move_speed;
		if (e->level[(int)e->pos.x][(int)(e->pos.y + e->dir.y * move_speed)] == 0)
			e->pos.y += e->dir.y * move_speed;
	}
	if (e->key.down)
	{
		if (e->level[(int)(e->pos.x - e->dir.x * move_speed)][(int)e->pos.y] == 0)
			e->pos.x -= e->dir.x * move_speed;
		if (e->level[(int)e->pos.x][(int)(e->pos.y - e->dir.y * move_speed)] == 0)
			e->pos.y -= e->dir.y * move_speed;
	}
	if (e->key.right)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(-rotation_speed) - e->dir.y * sin(-rotation_speed);
		e->dir.y = e->old_dir_x * sin(-rotation_speed) + e->dir.y * cos(-rotation_speed);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(-rotation_speed) - e->plane.y * sin(-rotation_speed);
		e->plane.y = e->old_plane_x * sin(-rotation_speed) + e->plane.y * cos(-rotation_speed);
	}
	if (e->key.left)
	{
		e->old_dir_x = e->dir.x;
		e->dir.x = e->dir.x * cos(rotation_speed) - e->dir.y * sin(rotation_speed);
		e->dir.y = e->old_dir_x * sin(rotation_speed) + e->dir.y * cos(rotation_speed);
		e->old_plane_x = e->plane.x;
		e->plane.x = e->plane.x * cos(rotation_speed) - e->plane.y * sin(rotation_speed);
		e->plane.y = e->old_plane_x * sin(rotation_speed) + e->plane.y * cos(rotation_speed);
	}
	check_prop_collide(e);
}
