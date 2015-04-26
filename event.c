#include <wolf.h>

void	key_left(t_wolf *wolf)
{
  wolf->x = 0;
  if (wolf->alpha > (M_PI))
    wolf->alpha = - M_PI;
  else if (wolf->alpha < - M_PI)
    wolf->alpha = M_PI;
  (wolf->alpha) += 0.1;
      SDL_SetRenderDrawColor(wolf->render, 0, 130 ,255, 1);
      draw_base(wolf);
  while (wolf->x < WIN_X)
  {
    raycasting(wolf);
    (wolf->x)++;
  }
}

void	key_right(t_wolf *wolf)
{
  wolf->x = 0;
  if (wolf->alpha > (M_PI))
    wolf->alpha = - M_PI;
  else if (wolf->alpha < - M_PI)
    wolf->alpha = M_PI;
  (wolf->alpha) -= 0.1;
      SDL_SetRenderDrawColor(wolf->render, 0, 130 ,255, 1);
      draw_base(wolf);
  while (wolf->x < WIN_X)
  {
    raycasting(wolf);
     (wolf->x)++;
  }
}

void	key_up(t_wolf *wolf)
{
  if (wolf->key_up == 1)
    {
      wolf->x = 0;
      wolf->x_pos_zero = wolf->x_pos_zero + MOVE_SPEED * cos(wolf->alpha);
      wolf->y_pos_zero = wolf->y_pos_zero + MOVE_SPEED * sin(wolf->alpha);
      SDL_SetRenderDrawColor(wolf->render, 0, 130 ,255, 1);
      draw_base(wolf);
   while (wolf->x < WIN_X)
  {
    raycasting(wolf);
     (wolf->x)++;
  }
    }
}

void	key_down(t_wolf *wolf)
{
  wolf->x = 0;
  wolf->x_pos_zero = wolf->x_pos_zero - MOVE_SPEED * cos(wolf->alpha);
  wolf->y_pos_zero = wolf->y_pos_zero - MOVE_SPEED * sin(wolf->alpha);
      SDL_SetRenderDrawColor(wolf->render, 0, 130 ,255, 1);
      draw_base(wolf);
   while (wolf->x < WIN_X)
  {
    raycasting(wolf);
     (wolf->x)++;
  }
}