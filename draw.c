/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 04:14:44 by rdantzer          #+#    #+#             */
/*   Updated: 2015/05/12 22:07:50 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

const int		h = WIN_Y;
const int		w = WIN_X;

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

void		draw(t_env *e)
{
	int			x;
	int			hit;
	int			wall_type;
	t_rgba		color;

	x = -1;
	hit = 0;
	while (++x < WIN_X)
	{
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayPosX = e->pos.x;
		double rayPosY = e->pos.y;
		double rayDirX = e->dir.x + e->plane.x * cameraX;
		double rayDirY = e->dir.y + e->plane.y * cameraX;
		//which box of the map we're in  
		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
		//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
		//Check if ray has hit a wall
		hit = (e->level[mapX][mapY] > 0);
		}
		wall_type = e->level[mapX][mapY];
		SDL_Surface *selected_surface;
		if (wall_type == 1)
			selected_surface = e->wall_greystone;
		else if (wall_type == 2)
			selected_surface = e->wall_colorstone;
		else if (wall_type == 3)
			selected_surface = e->wall_wood;
		else
			selected_surface = e->wall_bluestone;
		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
		//Calculate height of line to draw on screen
		int lineHeight = abs((int)(h / perpWallDist));
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;
		double wallX; //where exactly the wall was hit
		if (side == 1)
			wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
		else
			wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)TEX_WIDTH);
		if(side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;
		for(int y = drawStart; y < drawEnd; y++)
		{
			int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			t_rgba color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * texY + texX];
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
      double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
      if(side == 0 && rayDirX > 0)
      {
        floorXWall = mapX;
        floorYWall = mapY + wallX;
      }
      else if(side == 0 && rayDirX < 0)
      {
        floorXWall = mapX + 1.0;
        floorYWall = mapY + wallX;
      }
      else if(side == 1 && rayDirY > 0)
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY;
      }
      else
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY + 1.0;
      } 
      
      double distWall, distPlayer, currentDist;  

      distWall = perpWallDist;
      distPlayer = 0.0;

      if (drawEnd < 0)
      	drawEnd = h; //becomes < 0 when the integer overflows
      
      //draw the floor from drawEnd to the bottom of the screen
      for(int y = drawEnd + 1; y < h; y++)
      {
        currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);
         
        double currentFloorX = weight * floorXWall + (1.0 - weight) * e->pos.x;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * e->pos.y;
        
        int floorTexX, floorTexY;
        floorTexX = (int)(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
        floorTexY = (int)(currentFloorY * TEX_HEIGHT) % TEX_HEIGHT;
        
        //floor
        selected_surface = e->wall_wood;
        int checkerBoardPattern = ((int)currentFloorX + (int)currentFloorY) % 2;
        if(checkerBoardPattern == 0)
        	color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * floorTexY + floorTexX];
        else
			color = ((t_rgba *)selected_surface->pixels)[TEX_WIDTH * floorTexX + floorTexY];
		SDL_SetRenderDrawColor(e->render, color.b, color.g ,color.r, 1);
		//SDL_RenderDrawPoint(e->render, x, y);
        //SDL_RenderDrawPoint(e->render, x, h - y);
        //ceiling (symmetrical!)
      }
    }
}