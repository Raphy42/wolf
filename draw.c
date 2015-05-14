/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:14:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/13 19:58:32 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

void		bmp_draw(t_env *e, SDL_Surface *img, int startx, int starty)
{
	int		x;
	int		y;

	x = 0;
	while (x < img->w && x + startx < WIN_X)
	{
		y = 0;
		while (y < img->h && y + starty < WIN_Y)
		{
			SDL_Color color = ((SDL_Color *)img->pixels)[x + (y * img->w)];
			if (!(color.r == 255 && color.g == 0 && color.b == 255))
			{	
				SDL_SetRenderDrawColor(e->render, color.b, color.g ,color.r, 1);
				SDL_RenderDrawPoint(e->render, x+startx, y + starty);
			}
			y++;
		}
		x++;
	}
}

void			operate_rgba(t_rgba *c, char op, int value)
{
	if (op == '/')
	{
		c->r /= value;
		c->g /= value;
		c->b /= value;
	}
	else if (op == '+')
	{
		c->r += value;
		c->g += value;
		c->b += value;
	}
}

void			create_rgb(t_rgba *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

const int h = WIN_Y;
const int w = WIN_X;

void		draw_sky(t_env *e)
{
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h /2; y++)
		{
			SDL_SetRenderDrawColor(e->render, 0, 0, y * 255 / h, 1);
			SDL_RenderDrawPoint(e->render, x, y);
		}
	}
}

void		draw(t_env *e)
{
	int			x;
	int			hit;
	int			wall_type;
	t_rgba		color;
	t_floorcast f;
	t_raycast	r;
	int			side;

	x = -1;
	r.h = WIN_Y;
	r.w = WIN_X;
	draw_sky(e);
	while (++x < r.w)
	{
		      //calculate ray position and direction 
      r.camera_x = 2 * x / (double) (w) - 1; //x-coordinate in camera space     
      r.ray_pos.x = e->pos.x;
      r.ray_pos.y = e->pos.y;
      r.ray_dir.x = e->dir.x + e->plane.x*r.camera_x;
      r.ray_dir.y = e->dir.y + e->plane.y*r.camera_x;
     
      //which box of the map we're in  
      r.map_x = (int)(r.ray_pos.x);
      r.map_y = (int)(r.ray_pos.y);
      //length of ray from current position to next x or y-side
      //length of ray from one x or y-side to next x or y-side
      r.delta_dist.x = sqrt(1 + (r.ray_dir.y * r.ray_dir.y) / (r.ray_dir.x * r.ray_dir.x));
      r.delta_dist.y = sqrt(1 + (r.ray_dir.x * r.ray_dir.x) / (r.ray_dir.y * r.ray_dir.y));
      double perpWallDist;
       
      //what direction to step in x or y-direction (either +1 or -1)
      hit = 0; //was there a wall hit?
      //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (r.ray_dir.x < 0)
      {
        r.step_x = -1;
        r.side_dist.x = (r.ray_pos.x - r.map_x) * r.delta_dist.x;
      }
      else
      {
        r.step_x = 1;
        r.side_dist.x = (r.map_x + 1.0 - r.ray_pos.x) * r.delta_dist.x;
      }      
      if (r.ray_dir.y < 0)
      {
        r.step_y = -1;
        r.side_dist.y = (r.ray_pos.y - r.map_y) * r.delta_dist.y;
      }
      else
      {
        r.step_y = 1;
        r.side_dist.y = (r.map_y + 1.0 - r.ray_pos.y) * r.delta_dist.y;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (r.side_dist.x < r.side_dist.y)
        {
          r.side_dist.x += r.delta_dist.x;
          r.map_x += r.step_x;
          side = 0;
        }
        else
        {
          r.side_dist.y += r.delta_dist.y;
          r.map_y += r.step_y;
          side = 1;
        }
		//Check if ray has hit a wall
		if (e->level[r.map_x][r.map_y] > 0)
			hit = 1;				
		}
		wall_type = e->level[r.map_x][r.map_y];
		SDL_Surface *selected_surface;
		if (wall_type == 1)
			selected_surface = e->wall_greystone;
		else if (wall_type == 2)
			selected_surface = e->wall_colorstone;
		else if (wall_type == 3)
			selected_surface = e->wall_wood;
		else
			selected_surface = e->wall_bluestone;
		if (side == 0) perpWallDist = fabs((r.map_x - r.ray_pos.x + (1 - r.step_x) / 2) / r.ray_dir.x);
      else           perpWallDist = fabs((r.map_y - r.ray_pos.y + (1 - r.step_y) / 2) / r.ray_dir.y);
        
      //Calculate height of line to draw on screen
      int lineHeight = abs((int)(h / perpWallDist));
       
      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)
      	drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)
      	drawEnd = h - 1;
      
		//where exactly the wall was hit
		 double wallX; //where exactly the wall was hit
      if (side == 1) wallX = r.ray_pos.x + ((r.map_y - r.ray_pos.y + (1 - r.step_y) / 2) / r.ray_dir.y) * r.ray_dir.x;
      else           wallX = r.ray_pos.y + ((r.map_x - r.ray_pos.x + (1 - r.step_x) / 2) / r.ray_dir.x) * r.ray_dir.y;
      wallX -= floor((wallX));
       
      //x coordinate on the texture
      int texX = (int)(wallX * (double)(TEX_WIDTH));
      if(side == 0 && r.ray_dir.x > 0) texX = TEX_WIDTH - texX - 1;
      if(side == 1 && r.ray_dir.y < 0) texX = TEX_WIDTH - texX - 1;
      	for(int y = drawStart; y < drawEnd; y++)
		{
			int d = y * 256 - r.h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * texY + texX];
			if(side == 1)
			{
				color.r = (color.r >> 1) & 8355711;
				color.g = (color.g >> 1) & 8355711;
				color.b = (color.b >> 1) & 8355711;
			}
		SDL_SetRenderDrawColor(e->render, color.b, color.g ,color.r, 1);
		SDL_RenderDrawPoint(e->render, x, y);
		}
	//FLOOR CASTING
		//x, y position of the floor texel at the bottom of the wall
      //4 different wall directions possible
      //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
      if(side == 0 && r.ray_dir.x > 0)
      {
        f.floor_wall.x = r.map_x;
        f.floor_wall.y = r.map_y + wallX;
      }
      else if(side == 0 && r.ray_dir.x < 0)
      {
        f.floor_wall.x = r.map_x + 1.0;
        f.floor_wall.y = r.map_y + wallX;
      }
      else if(side == 1 && r.ray_dir.y > 0)
      {
        f.floor_wall.x = r.map_x + wallX;
        f.floor_wall.y = r.map_y;
      }
      else
      {
        f.floor_wall.x = r.map_x + wallX;
        f.floor_wall.y = r.map_y + 1.0;
      } 
      f.dist_wall = perpWallDist;
      f.dist_player = 0.0;

      if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows
      
      //draw the floor from drawEnd to the bottom of the screen
      for(int y = drawEnd + 1; y < h; y++)
      {
        f.current_dist = h / (2.0 * y - h); //you could make a small lookup table for this instead
        f.weight = (f.current_dist - f.dist_player) / (f.dist_wall - f.dist_player);
        f.current_floor.x = f.weight * f.floor_wall.x + (1.0 - f.weight) * e->pos.x;
        f.current_floor.y = f.weight * f.floor_wall.y + (1.0 - f.weight) * e->pos.y;
        f.floor_tex_x = (int)(f.current_floor.x * TEX_WIDTH) % TEX_WIDTH;
        f.floor_tex_y = (int)(f.current_floor.y * TEX_HEIGHT) % TEX_HEIGHT;
        
        //floor
        selected_surface = e->wall_wood;
        int checkerBoardPattern = ((int)f.current_floor.x + (int)f.current_floor.y) % 2;
        if(checkerBoardPattern == 0)
        	color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * f.floor_tex_y + f.floor_tex_x];
        else
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * f.floor_tex_x + f.floor_tex_y];
		SDL_SetRenderDrawColor(e->render, color.b, color.g ,color.r, 1);
		SDL_RenderDrawPoint(e->render, x, y);
      	//SDL_RenderDrawPoint(e->render, x, r.h - y);
      }
    }
}