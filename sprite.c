/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 05:31:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/22 02:01:58 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		list_split(t_sprite *src, t_sprite **front_ref, t_sprite **back_ref)
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

static t_sprite		*sort_list(t_sprite *a, t_sprite *b, int (*f)(t_sprite *a, t_sprite *b))
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

static void		merge_sort(t_sprite **head_ref, int (*f)(t_sprite *a, t_sprite *b))
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
		tmp->pos.x += tmp->dir.x;
		tmp->pos.y += tmp->dir.y;
		if (tmp->sprite == PARTICULE_BULLET)
		{
			if (e->level[(int)(tmp->pos.x + tmp->dir.x)]
				[(int)(tmp->pos.y + tmp->dir.y)])
			{
				tmp->value = 5;
				tmp->sprite = PARTICULE_EXPLOSION;
			}
			else
			{
				tmp->pos.x += tmp->dir.x;
				tmp->pos.y += tmp->dir.y;
			}
		}
		tmp->distance = ((e->pos.x - tmp->pos.x) *
			(e->pos.x - tmp->pos.x) + (e->pos.y - tmp->pos.y) *
			(e->pos.y - tmp->pos.y));
		tmp = tmp->next;
	}
	merge_sort(&e->sprite, &sort_sprite_by_distance);
}

int			add_new_sprite(t_sprite **head, t_sprite *new)
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
	new->sprite = get_texture_type(type);
	new->pos.x = i + (new->sprite == PARTICULE_BULLET ? e->dir.x : 0.5);
	new->pos.y = j + (new->sprite == PARTICULE_BULLET ? e->dir.x : 0.5);
	new->obstacle = (type == 'B' || type == 'A' || type == 'P') ? 1 : 0;
	new->destroy = 0;
	new->pick_up = (new->sprite == COLLEC_JEWELBOX);
	new->value = (new->sprite == COLLEC_JEWELBOX) ? 500 : 0;
	if (new->sprite == PARTICULE_BULLET)
	{
		new->dir.x = e->dir.x;
		new->dir.y = e->dir.y;
	}
	ft_fprintf(1, "created new sprite %d\n", new->sprite);
	return (new);
}

SDL_Surface		*select_sprite(t_sprite *s, t_env *e)
{
	if (s->sprite == PROP_LAMP)
		return (e->prop_lamp);
	else if (s->sprite == PROP_BARREL)
		return (e->prop_barrel);
	else if (s->sprite == PROP_ARMOR)
		return (e->prop_armor);
	else if (s->sprite == PROP_SKULLPILE)
		return (e->prop_skullpile);
	else if (s->sprite == COLLEC_JEWELBOX)
	{
		if (s->pick_up == 0)
			return (NULL);
		return (e->collec_jewelbox);
	}
	else if (s->sprite == PROP_PILLAR)
		return (e->prop_pillar);
	else if (s->sprite == PARTICULE_BULLET)
		return (e->particule_bullet);
	else if (s->sprite == PARTICULE_EXPLOSION)
	{
		if (s->value == 0)
			return (NULL);
		s->value--;
		return (e->particule_explosion);
	}
	else if (s->sprite < PROP_BARREL || s->sprite > PARTICULE_EXPLOSION)
		return (e->surface_error);
	return (NULL);
}

static void		print_sprite(t_env *e)
{
	t_sprite	*tmp = e->sprite;
	while (tmp->next != NULL)
	{
		ft_fprintf(1, "e->sprite.distance == %d type %d\n", tmp->distance, tmp->sprite);
		tmp = tmp->next;
	}
}

int				get_texture_type(int type)
{
	if (type == 'A')
		return (PROP_ARMOR);
	else if (type == 'B')
		return (PROP_BARREL);
	else if (type == 'J')
		return (COLLEC_JEWELBOX);
	else if (type == 'L')
		return (PROP_LAMP);
	else if (type == 'P')
		return (PROP_PILLAR);
	else if (type == 'S')
		return (PROP_SKULLPILE);
	return (SURFACE_ERROR);
}

void			sprite_cast(t_env *e, t_raycast *r)
{
	t_rgba		color;
	SDL_Surface	*selected_sprite;
	t_sprite	*s;

	s = e->sprite;
	print_sprite(e);
	update_sprite_pos(e);
	print_sprite(e);
	while (s->next != NULL)
	{
		ft_fprintf(1, "%dm %dtype\r", s->distance, s->sprite);
		if ((selected_sprite = select_sprite(s, e)) == NULL)
			selected_sprite = e->surface_error;
		double spriteX = s->pos.x - e->pos.x;
		double spriteY = s->pos.y - e->pos.y;
		double invDet = 1.0 / (e->plane.x * e->dir.y - e->dir.x * e->plane.y);
		double transformX = invDet * (e->dir.y * spriteX - e->dir.x * spriteY);
		double transformY = invDet * (-e->plane.y * spriteX + e->plane.x * spriteY);
		int spriteScreenX = (int)((r->w / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(r->h / (transformY)));
		int drawStartY = -spriteHeight / 2 + r->h / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + r->h / 2;
		if(drawEndY >= r->h)
			drawEndY = r->h - 1;
		int spriteWidth = abs((int)(r->h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= r->w)
			drawEndX = r->w - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * e->prop_barrel->w / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < r->w && transformY < r->z_buffer[stripe]) 
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y) * 256 - r->h * 128 + spriteHeight * 128; //256 and 128 factors to avoid doubles
				int texY = ((d * selected_sprite->h) / spriteHeight) / 256;
				color = ((t_rgba *)selected_sprite->pixels)[selected_sprite->w * texY + texX];
				if (!(color.r == 255 && color.g == 0 && color.b == 255))
					e->img_buffer[WIN_X * y + stripe] = create_color(color.b, color.g, color.r);
			}
		}
		s = s->next;
	}
}
