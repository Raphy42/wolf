/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvolonda <jvolonda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 14:44:00 by jvolonda          #+#    #+#             */
/*   Updated: 2015/04/25 18:02:45 by jvolonda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#define mapwidth 20
#define mapheight 20
#define UP 119
#define LEFT 97
#define RIGHT 100
#define DOWN 115
# include "libft.h"
# include "SDL.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct			s_wolf
{
	int					x;
	int					y;
	SDL_Window			*window;
	SDL_Event			event;
	SDL_Renderer		*render;
	int					pos_x;
	int					pos_y;
	int					map[mapwidth][mapheight];
}						t_wolf;

int			draw(t_wolf *e);
int			event(t_wolf *e);
void		fillmap(t_wolf *e);

#endif