/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 03:25:07 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/12 21:59:30 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>

static int			open_map(void)
{
	int				fd;

	fd = open(MAP_PATH, O_RDONLY);
	if (fd == -1)
		exit (ft_fprintf(2, "Unable to open map: %s\n", strerror(errno)));
	return (fd);
}

static void			parse_map(int fd, t_env *e)
{
	char			*line;
	int				size;
	char			**map;

	map = MAP;
	size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) > 255)
			exit (ft_fprintf(2, "Map is too big !"));
		map[size] = line;
		size++;
	}
	if (size == 0)
		exit (ft_fprintf(2, "Map is empty\n"));
	e->map_w = ft_strlen(map[0]);
	e->map_h = size;
	size = 0;
	ft_fprintf(1, "Map loaded (%d x %d)\n", e->map_w, e->map_h);
}

static void			convert_map(t_env *e)
{
	int				i;
	int				j;
	char			**map;

	map = MAP;
	i = -1;
	e->level = (int **)ft_memalloc(sizeof(int *) * e->map_h);
	while (++i < e->map_h)
	{
		e->level[i] = (int *)ft_memalloc(sizeof(int) * e->map_w);
		j = -1;
		while (++j < e->map_w)
		{
			e->level[i][j] = map[i][j] - '0';
			if (e->level[i][j] == 9)
			{
				e->level[i][j] = 0;
				e->pos.x = i;
				e->pos.y = j;
			}
			ft_fprintf(1, "%c", e->level[i][j] == 0 ? 0x20 : '#');
		}
		ft_fprintf(1, "\n");
	}
}

void				init(t_env *e)
{
	const int		fd = open_map();

	ft_bzero(e, sizeof(t_env));
	parse_map(fd, e);
	if (fd > 0)
		close(fd);
	SDL_Init(SDL_INIT_VIDEO);
	e->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN);
	e->render = SDL_CreateRenderer(e->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	SDL_RenderClear(e->render);
	e->pos.x = 2;
	e->pos.y = 2;
	e->dir.x = -1;
	e->dir.y = 0;
	e->plane.y = 0.66;
	e->plane.x = 0;
	convert_map(e);
}
