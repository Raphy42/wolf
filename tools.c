/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 16:31:55 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/18 09:07:24 by rdantzer         ###   ########.fr       */
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
	{COLLEC_JEWELBOX, "jewelbox.bmp"},
	{HUD_MAIN, "hud.bmp"}
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
}

int					check_prop_collide(t_env *e)
{
	int				i;

	i = -1;
	while (++i < e->sprite_count)
	{
		if ((int)e->pos.x == (int)e->sprite[i].pos.x && (int)e->pos.y == (int)e->sprite[i].pos.y &&
			e->sprite[i].pick_up)
			e->sprite[i].pick_up = 0;
	}
	return (0);
}

