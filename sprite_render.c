/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 01:06:49 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/28 11:18:50 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface			*select_sprite(t_sprite *s, t_env *e)
{
	if (s->sprite == PROP_LAMP || s->sprite == PROP_LAMP_FLICKER)
		return (e->prop_lamp);
	else if (s->sprite == PROP_BARREL)
		return (e->prop_barrel);
	else if (s->sprite == PROP_ARMOR)
		return (e->prop_armor);
	else if (s->sprite == PROP_SKULLPILE)
		return (e->prop_skullpile);
	else if (s->sprite == COLLEC_JEWELBOX)
		return (s->pick_up == 0 ? NULL : e->collec_jewelbox);
	else if (s->sprite == PROP_PILLAR)
		return (e->prop_pillar);
	else if (s->sprite == PARTICULE_BULLET)
		return (e->particule_bullet);
	else if (s->sprite == PARTICULE_EXPLOSION)
		return (s->light_source == 0 ? NULL : e->particule_explosion);
	else if (s->sprite < PROP_BARREL || s->sprite > PARTICULE_EXPLOSION)
		return (e->surface_error);
	return (NULL);
}

int					get_texture_type(int type)
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
	else if (type == 'l')
		return (PROP_LAMP_FLICKER);
	return (SURFACE_ERROR);
}

void				init_sprite_cast(t_env *e, t_raycast *r, t_sprite *s,
	t_spritecast *c)
{
	c->pos.x = s->pos.x - e->pos.x;
	c->pos.y = s->pos.y - e->pos.y;
	c->inv_det = 1.0 / (e->plane.x * e->dir.y - e->dir.x * e->plane.y);
	c->transform.x = c->inv_det * (e->dir.y * c->pos.x -
		e->dir.x * c->pos.y);
	c->transform.y = c->inv_det * (-e->plane.y * c->pos.x +
		e->plane.x * c->pos.y);
	c->sprite_screen_x = (int)((r->w / 2) * (1 + c->transform.x /
		c->transform.y));
	c->sprite_height = abs((int)(r->h / (c->transform.y)));
	c->draw_start_y = -c->sprite_height / 2 + r->h / 2;
	if (c->draw_start_y < 0)
		c->draw_start_y = 0;
	c->draw_end_y = c->sprite_height / 2 + r->h / 2;
	if (c->draw_end_y >= r->h)
		c->draw_end_y = r->h - 1;
	c->sprite_width = abs((int)(r->h / (c->transform.y)));
	c->draw_start_x = -c->sprite_width / 2 + c->sprite_screen_x;
	if (c->draw_start_x < 0)
		c->draw_start_x = 0;
	c->draw_end_x = c->sprite_width / 2 + c->sprite_screen_x;
	if (c->draw_end_x >= r->w)
		c->draw_end_x = r->w - 1;
}

static void			alpha_blending(t_env *e, t_rgba *color, int x, int y)
{
	Uint32			bg;
	t_rgba			color_bg;

	if (color->r == 0 && color->b == 255 && color->g == 0)
	{
		bg = e->img_buffer[WIN_X * y + x];
		color_bg.b = (bg >> 16) & 0xFF;
		color_bg.g = (bg >> 8) & 0xFF;
		color_bg.r = bg & 0xFF;
		color->r = (110 * .5) + (color_bg.r * (1.0 - .5));
		color->g = (110 * .5) + (color_bg.g * (1.0 - .5));
		color->b = (110 * .5) + (color_bg.b * (1.0 - .5));
	}
}

void				loop_sprite_cast(t_spritecast *c, SDL_Surface *sel,
	t_raycast *r, t_env *e)
{
	t_rgba		color;

	while (++c->stripe < c->draw_end_x)
	{
		c->tex_x = (int)(256 * (c->stripe - (-c->sprite_width / 2 +
			c->sprite_screen_x)) * e->prop_barrel->w / c->sprite_width) / 256;
		if (c->transform.y > 0 && c->stripe > 0 && c->stripe < r->w &&
			c->transform.y < r->z_buffer[c->stripe])
		{
			c->y = c->draw_start_y - 1;
			while (++c->y < c->draw_end_y)
			{
				c->d = (c->y) * 256 - r->h * 128 + c->sprite_height * 128;
				c->tex_y = ((c->d * sel->h) / c->sprite_height) / 256;
				color = ((t_rgba *)sel->pixels)[sel->w * c->tex_y + c->tex_x];
				if (sel == e->prop_lamp)
					alpha_blending(e, &color, c->stripe, c->y);
				if (!(color.r == 255 && color.g == 0 && color.b == 255))
					operate_rgba(&color, '/', c->shadow);
				if (!(color.r == 255 && color.g == 0 && color.b == 255))
					e->img_buffer[WIN_X * c->y + c->stripe] =
				create_color(color.b, color.g, color.r);
			}
		}
	}
}

void				sprite_cast(t_env *e, t_raycast *r)
{
	SDL_Surface		*selected_sprite;
	t_sprite		*s;
	t_spritecast	c;

	s = e->sprite;
	update_sprite_pos(e);
	while (s->next != NULL)
	{
		if ((selected_sprite = select_sprite(s, e)) == NULL)
		{
			s = s->next;
			continue ;
		}
		c.shadow = 5 / (e->shadows[(int)s->pos.x][(int)s->pos.y] + 1);
		init_sprite_cast(e, r, s, &c);
		c.stripe = c.draw_start_x - 1;
		loop_sprite_cast(&c, selected_sprite, r, e);
		s = s->next;
	}
}
