/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvolonda <jvolonda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 15:46:31 by jvolonda          #+#    #+#             */
/*   Updated: 2015/04/25 18:39:33 by jvolonda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			draw(t_wolf *e)
{
	SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	SDL_RenderClear(e->render);
	SDL_SetRenderDrawColor(e->render, 255, 0 ,0, 1);
	SDL_RenderDrawPoint(e->render, e->x, e->y);
	SDL_RenderPresent(e->render);
	return (1);
}

int			event(t_wolf *e)
{
	if (e->event.type == SDL_KEYDOWN)
	{
		if (e->event.key.keysym.sym == 27)
		{
			SDL_DestroyWindow(e->window);
			SDL_Quit();
			exit(1);
		}
		else if (e->event.key.keysym.sym == LEFT)
			e->x--;
		else if (e->event.key.keysym.sym == RIGHT)
			e->x++;
		else if (e->event.key.keysym.sym == UP)
			e->y--;
		else if (e->event.key.keysym.sym == DOWN)
			e->y++;
		draw(e);
	}
	return (1);
}

void		fillmap(t_wolf *e)
{
	int		fd;
	char	*s;
	int		y;
	int		x;
	int		tmp;

	x = 0;
	y = 0;
	tmp = 1;
	fd = open("map1", O_RDONLY);
	s = ft_strnew(50);
	while (tmp)
	{
		tmp = get_next_line(fd, &s);
		while (*s)
		{
			if (*s == '0' || *s == '1')
			{ 
				e->map[y][x] = *s - 48;
				printf("%d--x%d--y%d\n", e->map[y][x],x,y);
				x++;
			}
			s++;
		}
		x = 0;
		y++;
	}
}