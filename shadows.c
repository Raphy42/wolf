/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 05:44:42 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/28 13:51:46 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				update_shadow_buffer(t_env *e, double force, int x, int y)
{
	int				shadow;

	shadow = e->shadows[x][y];
	if ((int)force <= 0 || x > e->map_w - 1 || y > e->map_h - 1)
		return ;
	e->shadows[x][y] = shadow > force ? shadow : force;
	update_shadow_buffer(e, force - 1, x + 1, y);
	update_shadow_buffer(e, force - 1, x, y + 1);
	update_shadow_buffer(e, force - 1, x - 1, y);
	update_shadow_buffer(e, force - 1, x, y - 1);
}

void				update_all_shadows(t_env *e)
{
	t_sprite		*tmp;
	int				i;
	static short	frame;
	static double	force;

	tmp = e->sprite;
	i = -1;
	if (frame == 12)
	{
		frame = 0;
		force = 3 - 2 * cos(rand());
	}
	else
		frame++;
	while (++i < e->map_h)
		ft_bzero(e->shadows[i], sizeof(double) * e->map_w);
	while (tmp->next != NULL)
	{
		if (tmp->light_flicker)
			update_shadow_buffer(e, force,
				tmp->pos.x, tmp->pos.y);
		else
			update_shadow_buffer(e, tmp->light_source, tmp->pos.x, tmp->pos.y);
		tmp = tmp->next;
	}
	i = -1;
}

void				create_shadow_buffer(t_env *e)
{
	t_sprite		*tmp;
	int				i;
	int				j;

	i = -1;
	e->shadows = (double **)ft_memalloc(sizeof(double *) * e->map_h);
	while (++i < e->map_h)
		e->shadows[i] = (double *)ft_memalloc(sizeof(double) * e->map_w);
	i = -1;
	tmp = e->sprite;
	while (tmp->next != NULL)
	{
		update_shadow_buffer(e, tmp->light_source, tmp->pos.x, tmp->pos.y);
		tmp = tmp->next;
	}
	i = -1;
	while (++i < e->map_w)
	{
		j = -1;
		while (++j < e->map_h)
			ft_fprintf(2, "%d ", (int)e->shadows[i][j]);
		ft_putchar('\n');
	}
}
