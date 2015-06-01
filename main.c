/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 16:26:27 by lejoliwolf3d      #+#    #+#             */
/*   Updated: 2015/06/01 17:28:08 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
#include <signal.h>

char				**singleton_map(void)
{
	static char		*map[256];

	return (map);
}

void				sighandler(int sig)
{
	(void)sig;
	ft_fprintf(2, "\nKilled Wolf3D\n");
	exit (EXIT_FAILURE);
}

static void			loop_start(t_env *e)
{
	ft_bzero(e->img_buffer, DEFINE_ALAKON);
	e->time_start = e->time_end;
	e->time_end = SDL_GetTicks();
	e->frame_time = (e->time_end - e->time_start) / 1000.0;
}

static void			loop_end(t_env *e)
{
	draw(e);
	SDL_UpdateTexture(e->img, NULL, e->img_buffer, DEFINE_ALAKON2);
	if (e->player.hit)
		SDL_SetTextureColorMod(e->img, 255 -
			(100 - e->player.health), 0, 0);
	else
		SDL_SetTextureColorMod(e->img, 255, 255, 255);
	SDL_RenderCopy(e->render, e->img, NULL, NULL);
	draw_hud(e);
	SDL_RenderPresent(e->render);
	ft_fprintf(2, "\033[32;1m%ffps\r\033[0m", 1 / e->frame_time);
	update_all_shadows(e);
}

int					main(void)
{
	t_env			e;

	signal(SIGINT, &sighandler);
	ft_bzero(&e, sizeof(t_env));
	init(&e);
	create_texture_array(&e);
	create_shadow_buffer(&e);
	while (1)
	{
		loop_start(&e);
		while (SDL_PollEvent(&e.event))
			event(&e);
		run_event(&e);
		loop_end(&e);
	}
	return (0);
}
