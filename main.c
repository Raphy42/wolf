/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 16:26:27 by lejoliwolf3d      #+#    #+#             */
/*   Updated: 2015/05/14 16:32:25 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char				**singleton_map(void)
{
	static char		*map[256];

	return (map);
}

int					main(void)
{
	t_env			e;

	ft_bzero(&e, sizeof(t_env));
	init(&e);
	create_texture_array(&e);
	while (1)
	{
		e.time_start = e.time_end;
		e.time_end = SDL_GetTicks();
		e.frame_time = (e.time_end - e.time_start) / 1000.0;
		SDL_SetRenderDrawColor(e.render, 150, 150 , 150, 1);
		SDL_RenderClear(e.render);
		while(SDL_PollEvent(&e.event))
			event(&e);
		draw(&e);
		SDL_RenderPresent(e.render);
	}
	return (0);
}