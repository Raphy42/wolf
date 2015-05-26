/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 16:31:55 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/22 06:08:52 by rdantzer         ###   ########.fr       */
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

SDL_Surface			*load_texture(t_texture_type name)
{
	char			*path;
	SDL_Surface		*surface;

	path = g_textures[name].name;
	path = ft_strjoin("resources/", path);
	surface = SDL_LoadBMP(path);
	free(path);
	ft_fprintf(2, "Loading surface: %s %s\n", g_textures[name].name, SDL_GetError());
	ft_fprintf(2, "Surface information: %dw %dh\n\n", surface->w, surface->h);
	return (surface);
}

void				create_texture_array(t_env *e)
{
	SDL_Surface		*tmp;

	e->wall_greystone = load_texture(WALL_GREYSTONE);
	e->wall_colorstone = load_texture(WALL_COLORSTONE);
	e->wall_wood = load_texture(WALL_WOOD);
	e->wall_bluestone = load_texture(WALL_BLUESTONE);
	e->prop_barrel = load_texture(PROP_BARREL);
	e->prop_skullpile = load_texture(PROP_SKULLPILE);
	e->prop_armor = load_texture(PROP_ARMOR);
	e->prop_lamp = load_texture(PROP_LAMP);
	e->wall_bluestone_jail = load_texture(WALL_BLUESTONE_JAIL);
	e->collec_jewelbox = load_texture(COLLEC_JEWELBOX);
	e->wall_wood_paint = load_texture(WALL_WOOD_PAINT);
	e->hud = SDL_CreateTextureFromSurface(e->render, load_texture(HUD_MAIN));
	e->hud_bj_face = SDL_CreateTextureFromSurface(e->render, load_texture(HUD_BJ_FACE));
	e->prop_pillar = load_texture(PROP_PILLAR);
	e->hud_number = SDL_CreateTextureFromSurface(e->render, load_texture(HUD_NUMBER));
	e->hud_gun = SDL_CreateTextureFromSurface(e->render, load_texture(HUD_GUN));
	tmp = load_texture(WEAPON_ALL);
	Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
	SDL_SetColorKey(tmp, SDL_TRUE,colorkey);
	e->weapon_all = SDL_CreateTextureFromSurface(e->render, tmp);
	e->particule_bullet = load_texture(PARTICULE_BULLET);
	e->particule_explosion = load_texture(PARTICULE_EXPLOSION);
	e->surface_error = load_texture(SURFACE_ERROR);
	e->game_over = load_texture(GAME_OVER);
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
