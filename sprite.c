/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 05:31:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/18 08:27:00 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				create_new_sprite(t_env *e, int i, int j, int type)
{
	int			k;

	k = e->sprite_count;
	if (type == 'B')
		e->sprite[k].sprite = PROP_BARREL;
	else if (type == 'S')
		e->sprite[k].sprite = PROP_SKULLPILE;
	else if (type == 'A')
		e->sprite[k].sprite = PROP_ARMOR;
	else if (type == 'L')
		e->sprite[k].sprite = PROP_LAMP;
	else if (type == 'J')
		e->sprite[k].sprite = COLLEC_JEWELBOX;
	e->sprite[k].pos.x = i + .5;
	e->sprite[k].pos.y = j + .5;
	e->sprite[k].obstacle = (type == 'B' || type == 'A') ? 1 : 0;
	e->sprite[k].destroy = 0;
	e->sprite[k].pick_up = (type == 'J');
	e->sprite_count++;
	return (-e->sprite[k].obstacle);
}

void			sprite_cast(t_env *e, t_raycast *r)
{
	t_rgba		color;
	SDL_Surface	*selected_sprite;

	for(int i = 0; i < e->sprite_count; i++)
	{
		if (e->sprite[i].sprite == PROP_LAMP)
			selected_sprite = e->prop_lamp;
		else if (e->sprite[i].sprite == PROP_BARREL)
			selected_sprite = e->prop_barrel;
		else if (e->sprite[i].sprite == PROP_ARMOR)
			selected_sprite = e->prop_armor;
		else if (e->sprite[i].sprite == PROP_SKULLPILE)
			selected_sprite = e->prop_skullpile;
		else if (e->sprite[i].sprite == COLLEC_JEWELBOX)
		{
			selected_sprite = e->collec_jewelbox;
			if (e->sprite[i].pick_up == 0)
				continue ;
		}
		double spriteX = e->sprite[i].pos.x - e->pos.x;
		double spriteY = e->sprite[i].pos.y - e->pos.y;
		double invDet = 1.0 / (e->plane.x * e->dir.y - e->dir.x * e->plane.y); //required for correct matrix multiplication
		double transformX = invDet * (e->dir.y * spriteX - e->dir.x * spriteY);
		double transformY = invDet * (-e->plane.y * spriteX + e->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D       
		int spriteScreenX = (int)((r->w / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(r->h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
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
				int texY = ((d * e->prop_barrel->h) / spriteHeight) / 256;
				color = ((t_rgba *)selected_sprite->pixels)[selected_sprite->w * texY + texX];
				if (!(color.r == 255 && color.g == 0 && color.b == 255))
					e->img_buffer[WIN_X * y + stripe] = create_color(color.b, color.g, color.r);
			}
		}
	}
}
