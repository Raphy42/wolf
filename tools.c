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
		else if (e->event.key.keysym.sym == UP && e->key_up)
			key_up(e);
		else if (e->event.key.keysym.sym == DOWN && e->x_pos_zero > 0.5 && e->x_pos_zero < SIZE_MAP - 0.5 && e->y_pos_zero > 0.5 && e->y_pos_zero < SIZE_MAP - 0.5)
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
	int		i;

	y = 0;
	fd = open("map1", O_RDONLY);
	s = ft_strnew(20);
	while (get_next_line(fd, &s))
	{
		x = 0;
		i = 0;
		while (s[i])
		{
			if (s[i] == '0' || s[i] == '1')
			{ 
				e->map[y][x] = s[i] - 48;
				x++;
			}
			i++;
		}
		y++;
	}
	free(s);
}