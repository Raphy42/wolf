/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 04:33:37 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/26 05:14:26 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

Uint32				create_color(int r, int g, int b)
{
	return (((r << 8)+ g) << 8)+ b;
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
