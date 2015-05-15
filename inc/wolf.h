/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 14:44:00 by leboheader        #+#    #+#             */
/*   Updated: 2015/05/15 23:14:11 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "SDL.h"

# define MAP_PATH		"map1"
# define MAP			singleton_map();
# define M				e->map
# define WIN_X			1800
# define WIN_Y			1200
# define TEX_WIDTH		512
# define TEX_HEIGHT		512
# define KEY			e->event.key.keysym.sym

typedef enum			e_texture_type
{
	WALL_BLUESTONE,
	WALL_BLUESTONE_JAIL,
	WALL_COLORSTONE,
	WALL_GREYSTONE,
	WALL_MOSSY,
	WALL_WOOD,
	PROP_BARREL,
	PROP_SKULLPILE,
	PROP_ARMOR,
	PROP_LAMP,
	COLLEC_JEWELBOX
}						t_texture_type;

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
	t_pos				pos;
	t_texture_type		sprite;
	int					obstacle;
	int					destroy;
	int					pick_up;
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

typedef struct			s_env
{
	SDL_Window			*window;
	SDL_Event			event;
	SDL_Renderer		*render;
	double				time_start;
	double				time_end;
	double				frame_time;
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
	SDL_Surface			*wall_colorstone;
	SDL_Surface			*wall_bluestone;
	SDL_Surface			*wall_bluestone_jail;
	SDL_Surface			*prop_barrel;
	SDL_Surface			*prop_skullpile;
	SDL_Surface			*prop_armor;
	SDL_Surface			*prop_lamp;
	SDL_Surface			*collec_jewelbox;
	SDL_Texture			*img;
	Uint32				*img_buffer;
	t_key				key;
	t_sprite			sprite[256];
	int					sprite_count;
}						t_env;

char					**singleton_map(void);
void					event(t_env *e);
void					run_event(t_env *e);
void					init(t_env *e);
void					draw(t_env *e);
SDL_Surface				*load_texture(t_texture_type name);
void					bmp_draw(t_env *e, SDL_Surface *img, int startx, int starty);
void					create_texture_array(t_env *e);
int						check_prop_collide(t_env *e);

#endif
