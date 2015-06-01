/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 03:07:27 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/30 11:00:58 by rdantzer         ###   ########.fr       */
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

static void		game_routine(t_env *e)
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
}

static void		event_key_down(t_env *e)
{
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
			e->player.selected_weapon +=
			e->player.selected_weapon == 3 ? -3 : 1;
		else if (KEY == SDLK_x && e->player.weapon_state <= 5)
		{
			e->player.weapon_state = (6 - e->player.selected_weapon) * 5;
			if (e->player.selected_weapon)
				add_new_sprite(&e->sprite, create_new_sprite(e,
				e->pos.x, e->pos.y, PARTICULE_BULLET));
		}
	}
}

void			event(t_env *e)
{
	game_routine(e);
	event_key_down(e);
	if (e->event.type == SDL_KEYUP)
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
