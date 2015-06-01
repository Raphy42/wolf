/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 04:33:37 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/01 17:00:30 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float				lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}

Uint32				create_color(int r, int g, int b)
{
	return (((r << 8) + g) << 8) + b;
}

void				operate_rgba(t_rgba *c, char op, double value)
{
	if (op == '/')
	{
		c->r /= value;
		c->g /= value;
		c->b /= value;
	}
	else if (op == '+')
	{
		c->r += value;
		c->g += value;
		c->b += value;
	}
}

void				create_rgb(t_rgba *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void				alpha_blending(t_env *e, t_rgba *color, int x, int y)
{
	Uint32			bg;
	t_rgba			color_bg;

	if (color->r == 0 && color->b == 255 && color->g == 0)
	{
		bg = e->img_buffer[WIN_X * y + x];
		color_bg.b = (bg >> 16) & 0xFF;
		color_bg.g = (bg >> 8) & 0xFF;
		color_bg.r = bg & 0xFF;
		color->r = (255 * .5) + (color_bg.r * (1.0 - .5));
		color->g = (255 * .5) + (color_bg.g * (1.0 - .5));
		color->b = (255 * .5) + (color_bg.b * (1.0 - .5));
	}
}
