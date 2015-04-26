#include "wolf.h"

void	raycasting_rotate(t_wolf *wolf)
{
  float	nx_pos_one;
  float	ny_pos_one;
  
  nx_pos_one =
    wolf->x_pos_one * cos(wolf->alpha) - wolf->y_pos_one * sin(wolf->alpha);
  ny_pos_one = 
    wolf->x_pos_one * sin(wolf->alpha) + wolf->y_pos_one * cos(wolf->alpha);
  wolf->x_pos_one = nx_pos_one;
  wolf->y_pos_one = ny_pos_one;
}

void	raycasting_translation(t_wolf *wolf)
{
  float	nx_pos_one;
  float	ny_pos_one;

  nx_pos_one = wolf->x_pos_one + wolf->x_pos_zero;
  ny_pos_one = wolf->y_pos_one + wolf->y_pos_zero;
  wolf->x_pos_one = nx_pos_one;
  wolf->y_pos_one = ny_pos_one;
}

float	raycasting_intersection_in_y(t_wolf *wolf, int map[SIZE_MAP][SIZE_MAP])
{
  float	x_inter;
  float	y_inter;
  float	k_temp;
  float	k_y;
  float	vx;
  float	vy;

  vx = wolf->x_pos_one - wolf->x_pos_zero;
  vy = wolf->y_pos_one - wolf->y_pos_zero;
  k_y = 500;
  y_inter = 0;
  while (y_inter < SIZE_MAP)
    {
      k_temp = (y_inter - wolf->y_pos_zero) / vy;
      x_inter = wolf->x_pos_zero + k_temp * vx;
      if ((int)y_inter >= 0 &&(int)y_inter <= SIZE_MAP && (int)x_inter >= 0 &&
	  (int)x_inter <= SIZE_MAP)
	if (map[(int)y_inter][(int)x_inter] == 1 && k_temp < k_y && k_temp > 0 &&
	    map[(int)y_inter][(int)x_inter + 1] == 1 && k_temp < k_y && k_temp > 0)
	 k_y = k_temp;
     y_inter++;
    }
  return (k_y);
}

float	raycasting_intersection_in_x(t_wolf *wolf, int map[SIZE_MAP][SIZE_MAP])
{
  float	x_inter;
  float	y_inter;
  float	k_temp;
  float	k_x;
  float	vx;
  float	vy;

  vx = wolf->x_pos_one - wolf->x_pos_zero;
  vy = wolf->y_pos_one - wolf->y_pos_zero;
  k_x = 500;
  x_inter = 0;
  while (x_inter < SIZE_MAP)
    {
      k_temp = (x_inter - wolf->x_pos_zero) / vx;
      y_inter = wolf->y_pos_zero + k_temp * vy;
      if ((int)y_inter >= 0 &&(int)y_inter <= SIZE_MAP && (int)x_inter >= 0 &&
	  (int)x_inter <= SIZE_MAP)
	if (map[(int)y_inter][(int)x_inter] == 1 && k_temp < k_x && k_temp > 0 &&
	    map[(int)y_inter + 1][(int)x_inter] == 1 && k_temp < k_x && k_temp > 0)
	  k_x = k_temp;
      x_inter++;
    }
  return (k_x);
}

void	raycasting(t_wolf *wolf)
{
  float	p;
  float	d;
  float	k;
  float	k_y;
  float	k_x;

  p = 1;
  d = p / 2;
  wolf->x_pos_one = d;
  wolf->y_pos_one = (p * (WIN_X / 2 - wolf->x) / WIN_X);
  raycasting_rotate(wolf);
  raycasting_translation(wolf);
  k_y = raycasting_intersection_in_y(wolf, wolf->map);
  k_x = raycasting_intersection_in_x(wolf, wolf->map);
  if (k_x < k_y && k_x > 0)
    k = k_x;
  else
    k = k_y;
  draw(wolf, k);
}