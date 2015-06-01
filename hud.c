/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 09:06:55 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/01 17:36:41 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void				print_number(t_env *e, int n, int x, int y)
{
	SDL_Rect			src;
	SDL_Rect			dst;

	dst.x = x;
	dst.y = y;
	dst.w = 18;
	dst.h = 64;
	src.x = n * 9 + 1;
	src.y = 0;
	src.w = 9;
	src.h = 16;
	SDL_RenderCopy(e->render, e->hud_number, &src, &dst);
}

static void				print_score(t_env *e, int score, int x, int y)
{
	int					i;

	i = 0;
	if (score == 0)
		print_number(e, score % 10, x - i * 18, y);
	while (score > 0)
	{
		print_number(e, score % 10, x - i * 18, y);
		score /= 10;
		i++;
	}
}

static void				print_gun(t_env *e)
{
	SDL_Rect			src;
	const SDL_Rect		dest = {940, 670, 200, 110};
	const SDL_Rect		middle_dest = {MIDDLE_DEST};
	int					*anim;

	anim = &e->player.weapon_state;
	*anim += (*anim > 1) ? -1 : 0;
	src.x = e->player.selected_weapon * 49;
	src.y = 0;
	src.w = 49;
	src.h = 26;
	SDL_RenderCopy(e->render, e->hud_gun, &src, &dest);
	src.x = *anim / 5 * 64;
	src.y = e->player.selected_weapon * 64 + e->player.selected_weapon;
	src.w = 64;
	src.h = 64;
	SDL_SetTextureColorMod(e->weapon_all, SHADOW_FPS, SHADOW_FPS, SHADOW_FPS);
	SDL_RenderCopy(e->render, e->weapon_all, &src, &middle_dest);
}

static void				update_bj_face(t_env *e)
{
	SDL_Rect			face;
	SDL_Rect			selected_face;
	int					offset;
	int					index;

	offset = 5 - (e->player.health != 0 ? e->player.health / 20 : -11);
	index = e->key.left ? 0 : 1;
	index = e->key.right ? 2 : index;
	face.x = WIN_X / 2 - 100;
	face.y = WIN_Y - 130;
	face.w = 112;
	face.h = 115;
	selected_face.x = index * 25;
	selected_face.y = offset * 33;
	selected_face.w = 23;
	selected_face.h = 30;
	SDL_RenderCopy(e->render, e->hud_bj_face, &selected_face, &face);
}

void					draw_hud(t_env *e)
{
	const SDL_Rect		dst = {0, WIN_Y - 150, 1200, 150};
	const SDL_Rect		src = {0, 0, 1200, 150};

	SDL_RenderCopy(e->render, e->hud, &src, &dst);
	update_bj_face(e);
	print_score(e, e->player.health, 700, 710);
	print_score(e, e->player.score, 325, 710);
	print_score(e, 1, 130, 710);
	print_score(e, e->player.life, 450, 710);
	print_score(e, e->player.ammo, 870, 710);
	print_gun(e);
}
