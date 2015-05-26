/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 01:08:14 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/26 05:52:19 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		list_split(t_sprite *src, t_sprite **front_ref,
	t_sprite **back_ref)
{
	t_sprite	*fast;
	t_sprite	*slow;

	if (src == NULL || src->next == NULL)
	{
		*front_ref = src;
		*back_ref = NULL;
	}
	else
	{
		slow = src;
		fast = src->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_ref = src;
		*back_ref = slow->next;
		slow->next = NULL;
	}
}

static t_sprite	*sort_list(t_sprite *a, t_sprite *b,
	int (*f)(t_sprite *a, t_sprite *b))
{
	t_sprite	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((*f)(a, b))
	{
		result = a;
		result->next = sort_list(a->next, b, (*f));
	}
	else
	{
		result = b;
		result->next = sort_list(a, b->next, (*f));
	}
	return (result);
}

static void		merge_sort(t_sprite **head_ref,
	int (*f)(t_sprite *a, t_sprite *b))
{
	t_sprite	*head;
	t_sprite	*a;
	t_sprite	*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	list_split(head, &a, &b);
	merge_sort(&a, (*f));
	merge_sort(&b, (*f));
	*head_ref = sort_list(a, b, (*f));
}

static int		sort_sprite_by_distance(t_sprite *a, t_sprite *b)
{
	return ((a->distance >= b->distance));
}

void			update_sprite_pos(t_env *e)
{
	int			i;
	t_sprite	*tmp;

	i = -1;
	tmp = e->sprite;
	while (tmp->next != NULL)
	{
		update_sprite(tmp, e);
		tmp->pos.x += tmp->dir.x;
		tmp->pos.y += tmp->dir.y;
		tmp->distance = ((e->pos.x - tmp->pos.x) *
			(e->pos.x - tmp->pos.x) + (e->pos.y - tmp->pos.y) *
			(e->pos.y - tmp->pos.y));
		tmp = tmp->next;
	}
	merge_sort(&e->sprite, &sort_sprite_by_distance);
}
