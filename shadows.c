/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 05:44:42 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/26 06:31:44 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			update_shadow_buffer(t_env *e, t_sprite *s, int x, int y)
{
	if (!s->light_source)
		return ;
	if (e->shadows[x][y] > .5)
		return ;
	e->shadows[x][y] += ((x - s->pos.x) *
			(x - s->pos.x) + (y - s->pos.y) *
			(y - s->pos.y));
	if (x != e->map_w - 1)
		update_shadow_buffer(e, s, x + 1, y);
	if (y != e->map_h - 1)
		update_shadow_buffer(e, s, x, y + 1);
	if (x != 0)
		update_shadow_buffer(e, s, x - 1, y);
	if (y != 0)
		update_shadow_buffer(e, s, x, y - 1);
}

void			create_shadow_buffer(t_env *e)
{
	t_sprite	*tmp;
	int			i;

	i = -1;
	e->shadows = (double **)ft_memalloc(sizeof(double *) * e->map_h);
	while (++i < e->map_h)
		e->shadows[i] = (double *)ft_memalloc(sizeof(double) * e->map_w);
	i = -1;
	tmp = e->sprite;
	while (tmp->next != NULL)
	{
		update_shadow_buffer(e, tmp, tmp->pos.x, tmp->pos.y);
		tmp = tmp->next;
	}
}
