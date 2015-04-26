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
#define SIZE_MAP 20
#define UP 119
#define LEFT 97
#define RIGHT 100
#define DOWN 115
#define WIN_X 800
#define WIN_Y 600
#define MOVE_SPEED 0.5
# include "libft.h"
# include "SDL.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct			s_wolf
{
	int					x;
	int					y;
	SDL_Window			*window;
	SDL_Event			event;
	SDL_Renderer		*render;
	int	key_up;
	float	x_pos_zero;
	float	y_pos_zero;
	float	alpha;
	float	x_pos_one;
	float	y_pos_one;
	int					map[mapwidth][mapheight];
}						t_wolf;

int			draw(t_wolf *e, float k);
int			event(t_wolf *e);
void		fillmap(t_wolf *e);
void		draw_base(t_wolf *e);

void	key_left(t_wolf *wolf);
void	key_right(t_wolf *wolf);
void	key_up(t_wolf *wolf);
void	key_down(t_wolf *wolf);

void	raycasting(t_wolf *wolf);

#endif