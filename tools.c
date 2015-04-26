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

void	draw_wall(t_wolf *wolf, int top, int bottom)
{
	while (top <= bottom)
	{
		SDL_RenderDrawPoint(wolf->render, wolf->x, top);
		top++;
	}
}

int			draw(t_wolf *e, float k)
{
	int	middle;
	int	wall_middle_height;
	int	top;
	int	bottom;


	//SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	//SDL_RenderClear(e->render);
	e->key_up = 1;
	middle = WIN_Y / 2;
	wall_middle_height = WIN_Y / (2 * k);
	top = middle - wall_middle_height;
	bottom = middle + wall_middle_height;
	SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	draw_wall(e, top, bottom);
	return (1);
}

int			event(t_wolf *e)
{
	if (e->event.type == SDL_KEYDOWN)
	{
		printf("clic:%d\n",e->event.key.keysym.sym);
		if (e->event.key.keysym.sym == 27)
		{
			SDL_DestroyWindow(e->window);
			SDL_Quit();
			exit(1);
		}
		else if (e->event.key.keysym.sym == LEFT)
			key_left(e);
		else if (e->event.key.keysym.sym == RIGHT)
			key_right(e);
		else if (e->event.key.keysym.sym == UP)
			key_up(e);
		else if (e->event.key.keysym.sym == DOWN)
			key_down(e);
		SDL_RenderPresent(e->render);
	}
	return (1);
}

void		fillmap(t_wolf *e)
{
	int		fd;
	char	*s;
	int		y;
	int		x;

	x = 0;
	y = 0;
	fd = open("map1", O_RDONLY);
	s = ft_strnew(50);
	while (get_next_line(fd, &s))
	{
		while (*s)
		{
			if (*s == '0' || *s == '1')
			{ 
				e->map[y][x] = *s - 48;
				x++;
			}
			s++;
		}
		x = 0;
		y++;
	}
}