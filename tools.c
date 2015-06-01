/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 16:31:55 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/01 17:11:11 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

const t_texture_descriptor		g_textures[] = {
	{WALL_BLUESTONE, "bluestone.bmp"},
	{WALL_BLUESTONE_JAIL, "bluestone_jail.bmp"},
	{WALL_COLORSTONE, "colorstone.bmp"},
	{WALL_GREYSTONE, "greystone.bmp"},
	{WALL_MOSSY, "moss.bmp"},
	{WALL_WOOD, "wood.bmp"},
	{WALL_WOOD_PAINT, "wood_painting.bmp"},
	{PROP_BARREL, "barrel.bmp"},
	{PROP_SKULLPILE, "skullpile.bmp"},
	{PROP_ARMOR, "armor.bmp"},
	{PROP_LAMP, "lamp.bmp"},
	{PROP_LAMP_FLICKER, NULL},
	{PROP_PILLAR, "pillar.bmp"},
	{COLLEC_JEWELBOX, "jewelbox.bmp"},
	{HUD_MAIN, "hud.bmp"},
	{HUD_BJ_FACE, "hud_bj_face.bmp"},
	{HUD_NUMBER, "hud_number.bmp"},
	{HUD_GUN, "hud_gun.bmp"},
	{WEAPON_ALL, "weapon_all.bmp"},
	{PARTICULE_BULLET, "bullet.bmp"},
	{PARTICULE_EXPLOSION, "explosion.bmp"},
	{SURFACE_ERROR, "error.bmp"},
	{GAME_OVER, "game_over.bmp"}
};

SDL_Surface			*load_surface(t_texture_type name)
{
	char			*path;
	SDL_Surface		*surface;

	path = g_textures[name].name;
	path = ft_strjoin("resources/", path);
	surface = SDL_LoadBMP(path);
	free(path);
	ft_fprintf(2, "Loading surface: %s %s\n",
		g_textures[name].name, SDL_GetError());
	ft_fprintf(2, "Surface information: %dw %dh\n\n",
		surface->w, surface->h);
	return (surface);
}

static SDL_Texture	*load_texture_from_surface(t_env *e, t_texture_type type,
	int alpha)
{
	SDL_Surface		*tmp;
	SDL_Texture		*texture;
	Uint32			color_key;

	tmp = load_surface(type);
	if (alpha)
	{
		color_key = SDL_MapRGB(tmp->format, 255, 0, 255);
		SDL_SetColorKey(tmp, SDL_TRUE, color_key);
	}
	if (tmp == NULL)
		exit (ft_fprintf(2, "Texture error\n"));
	texture = SDL_CreateTextureFromSurface(e->render, tmp);
	SDL_FreeSurface(tmp);
	return (texture);
}

void				create_texture_array(t_env *e)
{
	e->wall_greystone = load_surface(WALL_GREYSTONE);
	e->wall_colorstone = load_surface(WALL_COLORSTONE);
	e->wall_wood = load_surface(WALL_WOOD);
	e->wall_bluestone = load_surface(WALL_BLUESTONE);
	e->prop_barrel = load_surface(PROP_BARREL);
	e->prop_skullpile = load_surface(PROP_SKULLPILE);
	e->prop_armor = load_surface(PROP_ARMOR);
	e->prop_lamp = load_surface(PROP_LAMP);
	e->wall_bluestone_jail = load_surface(WALL_BLUESTONE_JAIL);
	e->collec_jewelbox = load_surface(COLLEC_JEWELBOX);
	e->wall_wood_paint = load_surface(WALL_WOOD_PAINT);
	e->particule_bullet = load_surface(PARTICULE_BULLET);
	e->particule_explosion = load_surface(PARTICULE_EXPLOSION);
	e->surface_error = load_surface(SURFACE_ERROR);
	e->prop_pillar = load_surface(PROP_PILLAR);
	e->game_over = load_surface(GAME_OVER);
	e->hud = load_texture_from_surface(e, HUD_MAIN, 0);
	e->hud_bj_face = load_texture_from_surface(e, HUD_BJ_FACE, 0);
	e->hud_number = load_texture_from_surface(e, HUD_NUMBER, 0);
	e->hud_gun = load_texture_from_surface(e, HUD_GUN, 0);
	e->weapon_all = load_texture_from_surface(e, WEAPON_ALL, 1);
}

void				check_prop_collide(t_env *e)
{
	t_sprite		*tmp;

	tmp = e->sprite;
	while (tmp->next != NULL)
	{
		if (((int)e->pos.x == (int)tmp->pos.x) && ((int)e->pos.y ==
			(int)tmp->pos.y && tmp->pick_up))
		{
			tmp->pick_up = 0;
			e->player.score += tmp->value;
		}
		tmp = tmp->next;
	}
}
