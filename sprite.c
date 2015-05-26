/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 05:31:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/26 11:01:52 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			update_sprite(t_sprite *tmp, t_env *e)
{
	if (tmp->sprite == PARTICULE_BULLET)
	{
		if (e->level[(int)(tmp->pos.x + tmp->dir.x)]
			[(int)(tmp->pos.y + tmp->dir.y)])
		{
			tmp->light_source = 10;
			tmp->dir.x = 0;
			tmp->dir.y = 0;
			tmp->sprite = PARTICULE_EXPLOSION;
			if ((int)tmp->pos.x == (int)e->pos.x &&
				(int)tmp->pos.y == (int)e->pos.y)
			{
				e->player.health -= 10;
				e->player.hit = 1;
			}
		}
	}
}

int				add_new_sprite(t_sprite **head, t_sprite *new)
{
	t_sprite	*tmp;

	tmp = (*head);
	if (tmp == NULL)
		(*head) = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (-new->obstacle);
}

t_sprite		*create_new_sprite(t_env *e, int i, int j, int type)
{
	t_sprite	*new;

	new = (t_sprite *)malloc(sizeof(t_sprite));
	ft_bzero(new, sizeof(t_sprite));
	new->sprite = type;
	if (new->sprite == PARTICULE_BULLET)
		new->dir = e->dir;
	new->pos.x = i + (new->sprite != PARTICULE_BULLET ? .5 : 0);
	new->pos.y = j + (new->sprite != PARTICULE_BULLET ? .5 : 0);
	new->obstacle = (new->sprite == PROP_BARREL ||
		new->sprite == PROP_ARMOR || new->sprite == PROP_PILLAR) ? 1 : 0;
	new->light_source = (new->sprite == PROP_LAMP || new->sprite == PROP_LAMP + 1 ? 3 : 0);
	new->light_source = (new->sprite == PARTICULE_BULLET ? 3 : new->light_source);
	new->light_flicker = (new->sprite == PROP_LAMP_FLICKER);
	new->destroy = 0;
	new->pick_up = (new->sprite == COLLEC_JEWELBOX);
	new->value = (new->sprite == COLLEC_JEWELBOX) ? 500 : 0;
	return (new);
}
