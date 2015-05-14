/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 16:31:55 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/13 17:46:19 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

const t_texture_descriptor		g_textures[] = {
	{WALL_BLUESTONE, "bluestone.bmp"},
	{WALL_COLORSTONE, "colorstone.bmp"},
	{WALL_GREYSTONE, "greystone.bmp"},
	{WALL_MOSSY, "moss.bmp"},
	{WALL_PURPLESTONE, "purplestone.png"},
	{WALL_REDBRICK, "redbrick.png"},
	{WALL_WOOD, "wood.bmp"},
	{PROP_BARREL, "barrel.png"},
	{PROP_PILLAR, "pillar.png"},
	{PROP_GREENLIGHT, "greenlight.png"}
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
}