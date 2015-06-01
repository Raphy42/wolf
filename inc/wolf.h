/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 14:44:00 by rdantzer          #+#    #+#             */
/*   Updated: 2015/06/01 18:05:16 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "SDL.h"

# define DEFAULT_POS_X		e->default_pos.x;
# define DEFAULT_POS_Y		e->default_pos.y;
# define KEY				e->event.key.keysym.sym
# define L					e->level
# define M					e->map
# define MAP				singleton_map();
# define MAP_PATH			".map1"
# define MIDDLE_DEST		WIN_X / 2 - 256, WIN_RAY_Y - 512, 512, 512
# define PORTRAIT			503, 20, 614, 134
# define ROT				rotation_speed
# define SHADOW_FPS			255 * e->shadows[(int)e->pos.x][(int)e->pos.y] / 3
# define TEX_HEIGHT			512
# define TEX_WIDTH			512
# define WIN_RAY_Y			(WIN_Y - 150)
# define WIN_X				1200
# define WIN_Y				800
# define COLOR				create_color(color.b, color.g, color.r)
# define DEFINE_ALAKON		sizeof(Uint32) * WIN_X * WIN_Y
# define DEFINE_ALAKON2		WIN_X * sizeof(Uint32)

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
	PROP_LAMP_FLICKER,
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

typedef struct			s_texture_descriptor
{
	t_texture_type		type;
	char				*name;
}						t_texture_descriptor;

typedef struct			s_texture_array
{
	t_texture_type		type;
	SDL_Surface			*surface;
}						t_texture_array;

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
	int					light_source;
	int					light_flicker;
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_raycast
{
	int					d;
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
	int					line_height;
	int					tex_x;
	int					tex_y;
	int					side;
	int					draw_start;
	int					draw_end;
	double				z_buffer[WIN_X];
	double				shadow;
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
	int					x;
	int					y;
	double				shadow;
	double				shadow_lerp;
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
	double				shadow;
}						t_spritecast;

typedef struct			s_env
{
	double				**shadows;
	double				frame_time;
	double				hit_point;
	double				old_dir_x;
	double				old_plane_x;
	double				time_end;
	double				time_start;
	int					**level;
	int					map_h;
	int					map_w;
	SDL_Event			event;
	SDL_Renderer		*render;
	SDL_Surface			*collec_jewelbox;
	SDL_Surface			*game_over;
	SDL_Surface			*particule_bullet;
	SDL_Surface			*particule_explosion;
	SDL_Surface			*prop_armor;
	SDL_Surface			*prop_barrel;
	SDL_Surface			*prop_lamp;
	SDL_Surface			*prop_pillar;
	SDL_Surface			*prop_skullpile;
	SDL_Surface			*surface_error;
	SDL_Surface			*wall_bluestone;
	SDL_Surface			*wall_bluestone_jail;
	SDL_Surface			*wall_colorstone;
	SDL_Surface			*wall_greystone;
	SDL_Surface			*wall_wood;
	SDL_Surface			*wall_wood_paint;
	SDL_Texture			*hud;
	SDL_Texture			*hud_bj_face;
	SDL_Texture			*hud_gun;
	SDL_Texture			*hud_number;
	SDL_Texture			*img;
	SDL_Texture			*red_damage;
	SDL_Texture			*weapon_all;
	SDL_Window			*window;
	t_key				key;
	t_player			player;
	t_pos				default_pos;
	t_pos				dir;
	t_pos				plane;
	t_pos				pos;
	t_rgba				color;
	t_sprite			*sprite;
	Uint32				*img_buffer;
}						t_env;

char					**singleton_map(void);
float					lerp(float v0, float v1, float t);
int						add_new_sprite(t_sprite **head, t_sprite *new);
int						get_texture_type(int type);
SDL_Surface				*load_texture(t_texture_type name);
t_sprite				*create_new_sprite(t_env *e, double i, double j,
	int type);
Uint32					create_color(int r, int g, int b);
void					alpha_blending(t_env *e, t_rgba *color, int x, int y);
void					check_prop_collide(t_env *e);
void					create_rgb(t_rgba *c, int r, int g, int b);
void					create_shadow_buffer(t_env *e);
void					create_texture_array(t_env *e);
void					draw(t_env *e);
void					draw_hud(t_env *e);
void					event(t_env *e);
void					floor_cast(t_env *e, t_raycast *r, int x);
void					init(t_env *e);
void					init_ray_cast(t_env *e, t_raycast *r, int x);
void					operate_rgba(t_rgba *c, char op, double value);
void					ray_cast(t_env *e, t_raycast *r);
void					run_event(t_env *e);
void					sprite_cast(t_env *e, t_raycast *r);
void					update_all_shadows(t_env *e);
void					update_bullet_shadow_buffer(t_env *e);
void					update_sprite(t_sprite *tmp, t_env *e);
void					update_sprite_pos(t_env *e);

#endif
