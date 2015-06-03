/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 14:12:38 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/03 17:02:45 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		putpixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8		*pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

static void		draw_point(t_env *e, int x, int y)
{
	const int	x_step = MINIMAP_W / e->map_w;
	const int	y_step = MINIMAP_H / e->map_h;
	int			i;
	int			j;

	if (!e->level[x][y])
	{
		j = (y * y_step) - 1;
		while (++j < y_step * (y + 1))
		{
			i = (x * x_step) - 1;
			while (++i < x_step * (x + 1))
				putpixel(e->minimap, j, i,
					create_color(SHADOW_MINI, SHADOW_MINI, SHADOW_MINI));
		}
	}
}

void			init_minimap(t_env *e)
{
	int			i;
	int			j;
	Uint32		colorkey;

	i = -1;
	while (++i < e->map_h)
	{
		j = -1;
		while (++j < e->map_w)
			draw_point(e, i, j);
	}
	colorkey = 0;
	SDL_SetColorKey(e->minimap, SDL_TRUE, colorkey);
	e->hud_minimap = SDL_CreateTextureFromSurface(e->render, e->minimap);
}

void			display_minimap(t_env *e)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = 0;
	dst.w = MINIMAP_H;
	dst.h = MINIMAP_H;
	SDL_RenderCopy(e->render, e->hud_minimap, NULL, &dst);
}
