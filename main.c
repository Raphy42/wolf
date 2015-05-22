/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 16:26:27 by lejoliwolf3d      #+#    #+#             */
/*   Updated: 2015/05/22 01:42:26 by rdantzer         ###   ########.fr       */
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
	exit (EXIT_FAILURE);
}

int					main(void)
{
	t_env			e;

	signal(SIGINT, &sighandler);
	ft_bzero(&e, sizeof(t_env));
	init(&e);
	create_texture_array(&e);
	while (1)
	{
		ft_bzero(e.img_buffer, sizeof(Uint32) * WIN_X * WIN_Y);
		e.time_start = e.time_end;
		e.time_end = SDL_GetTicks();
		e.frame_time = (e.time_end - e.time_start) / 1000.0;
		SDL_SetRenderDrawColor(e.render, 150, 150 , 150, 0);
		SDL_RenderClear(e.render);
		while(SDL_PollEvent(&e.event))
			event(&e);
		run_event(&e);
		draw(&e);
		SDL_UpdateTexture(e.img, NULL, e.img_buffer, WIN_X * sizeof(Uint32));
		SDL_RenderCopy(e.render, e.img, NULL, NULL);
		draw_hud(&e);
		SDL_RenderPresent(e.render);
		ft_bzero(e.img_buffer, sizeof(Uint32) * WIN_X * WIN_Y);
		ft_fprintf(2, "\033[1m%ffps\r\033[0m", 1 / e.frame_time);
	}
	return (0);
}
