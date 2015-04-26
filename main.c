/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvolonda <jvolonda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 16:26:27 by jvolonda          #+#    #+#             */
/*   Updated: 2015/04/25 17:47:09 by jvolonda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			main(void)
{
	t_wolf	e;

	ft_bzero(&e, sizeof(t_wolf));
	SDL_Init(SDL_INIT_VIDEO);
	e.window = SDL_CreateWindow( "wolf3d",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);
	e.render = SDL_CreateRenderer(e.window,-1,SDL_RENDERER_ACCELERATED);
	fillmap(&e);
	SDL_SetRenderDrawColor(e.render, 0, 0 ,0, 1);
	SDL_RenderClear(e.render);
	e.y_pos_zero = 10;
	e.x_pos_zero = 10;
	while (1)
	{
		while(SDL_PollEvent(&e.event))
			event(&e);
	}
	return (0);
}