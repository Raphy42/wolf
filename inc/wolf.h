/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 14:44:00 by leboheader        #+#    #+#             */
/*   Updated: 2015/05/26 00:15:16 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "SDL.h"

# define MAP_PATH		"map1"
# define MAP			singleton_map();
# define M				e->map
# define WIN_X			1200
# define WIN_Y			800
# define WIN_RAY_Y		(WIN_Y - 150)
# define TEX_WIDTH		512
# define TEX_HEIGHT		512
# define PORTRAIT		503, 20, 614, 134
# define KEY			e->event.key.keysym.sym
# define DEFAULT_POS_X	e->default_pos.x;
# define DEFAULT_POS_Y	e->default_pos.y;

typedef enum			e_texture_type
{
	WALL_BLUESTONE,
	WALL_BLUESTONE_JAIL,
	WALL_COLORSTONE,
	WALL_GREYSTONE,
	WALL_MOSSY,
	WALL_WOOD,
	WALL_WOOD_PAINT,
	PROP_BARREL,
	PROP_SKULLPILE,
	PROP_ARMOR,
	PROP_LAMP,
	PROP_PILLAR,
	COLLEC_JEWELBOX,
	HUD_MAIN,
	HUD_BJ_FACE,
	HUD_NUMBER,
	HUD_GUN,
	WEAPON_ALL,
	PARTICULE_BULLET,
	PARTICULE_EXPLOSION,
	SURFACE_ERROR,
	GAME_OVER
}						t_texture_type;

typedef struct			s_player
{
	int					score;
	int					health;
	int					life;
	int					selected_weapon;
	int					weapon_state;
	int					ammo;
	int					hit;
}						t_player;

typedef struct			s_key
{
	int					left;
	int					right;
	int					up;
	int					down;
}						t_key;

typedef struct			s_rgba
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
}						t_rgba;

typedef struct			s_texture_descriptor
{
	t_texture_type		type;
	char				*name;
}						t_texture_descriptor;

typedef struct			s_pos
{
	double				x;
	double				y;
}						t_pos;

typedef struct			s_sprite
{
	t_texture_type		sprite;
	t_pos				pos;
	t_pos				dir;
	int					obstacle;
	int					destroy;
	int					pick_up;
	int					value;
	int					distance;
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_raycast
{
	int					w;
	int					h;
	double				camera_x;
	t_pos				ray_pos;
	t_pos				ray_dir;
	int					map_x;
	int					map_y;
	t_pos				side_dist;
	t_pos				delta_dist;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	double				wall_x;
	int					side;
	int					draw_start;
	int					draw_end;
	double				z_buffer[WIN_X];
}						t_raycast;

typedef struct			s_floorcast
{
	t_pos				floor_wall;
	double				dist_wall;
	double				dist_player;
	double				current_dist;
	double				weight;
	t_pos				current_floor;
	int					floor_tex_x;
	int					floor_tex_y;
}						t_floorcast;

typedef struct			s_spritecast
{
	t_pos				pos;
	double				inv_det;
	t_pos				transform;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_x;
	int					draw_start_y;
	int					draw_end_x;
	int					draw_end_y;
	double				sprite_width;
	int					stripe;
	int					tex_x;
	int					tex_y;
	int					d;
	int					y;
}						t_spritecast;

typedef struct			s_env
{
	SDL_Window			*window;
	SDL_Event			event;
	SDL_Renderer		*render;
	double				time_start;
	double				time_end;
	double				frame_time;
	t_pos				default_pos;
	t_pos				pos;
	t_pos				dir;
	t_pos				plane;
	int					map_w;
	int					map_h;
	double				old_dir_x;
	double				old_plane_x;
	t_rgba				color;
	int					**level;
	double				hit_point;
	SDL_Surface			*wall_greystone;
	SDL_Surface			*wall_wood;
	SDL_Surface			*wall_wood_paint;
	SDL_Surface			*wall_colorstone;
	SDL_Surface			*wall_bluestone;
	SDL_Surface			*wall_bluestone_jail;
	SDL_Surface			*prop_barrel;
	SDL_Surface			*prop_skullpile;
	SDL_Surface			*prop_armor;
	SDL_Surface			*prop_lamp;
	SDL_Surface			*prop_pillar;
	SDL_Surface			*collec_jewelbox;
	SDL_Surface			*particule_bullet;
	SDL_Surface			*particule_explosion;
	SDL_Surface			*surface_error;
	SDL_Surface			*game_over;
	SDL_Texture			*red_damage;
	SDL_Texture			*hud_bj_face;
	SDL_Texture			*hud_number;
	SDL_Texture			*hud_gun;
	SDL_Texture			*weapon_all;
	SDL_Texture			*hud;
	SDL_Texture			*img;
	Uint32				*img_buffer;
	t_key				key;
	t_sprite			*sprite;
	t_player			player;

}						t_env;

Uint32					create_color(int r, int g, int b);
char					**singleton_map(void);
void					event(t_env *e);
void					run_event(t_env *e);
void					init(t_env *e);
void					draw(t_env *e);
SDL_Surface				*load_texture(t_texture_type name);
void					create_texture_array(t_env *e);
void					check_prop_collide(t_env *e);
int						add_new_sprite(t_sprite **head, t_sprite *new);
void					sprite_cast(t_env *e, t_raycast *r);
t_sprite				*create_new_sprite(t_env *e, int i, int j, int type);
void					draw_hud(t_env *e);
int						get_texture_type(int type);

#endif
