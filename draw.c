#include "wolf.h"

void	draw_wall(t_wolf *wolf, int top, int bottom)
{
	while (top <= bottom)
	{
		SDL_RenderDrawPoint(wolf->render, wolf->x, top);
		top++;
	}
}

int			draw(t_wolf *e, float k)
{
	int	middle;
	int	wall_middle_height;
	int	top;
	int	bottom;


	//SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	//SDL_RenderClear(e->render);
		e->key_up = 1;
		middle = WIN_Y / 2;
		wall_middle_height = WIN_Y / (2 * k);
		top = middle - wall_middle_height;
		bottom = middle + wall_middle_height;
		SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
		draw_wall(e, top, bottom);
	//printf("k:%f\n",k);
	if (k < 1)
		e->key_up = 0;
	return (1);
}

void	draw_base(t_wolf *e)
{
	int	x;
	int	y;

	y = 0;
	SDL_SetRenderDrawColor(e->render, 0, 0 ,0, 1);
	SDL_RenderClear(e->render);
	SDL_SetRenderDrawColor(e->render, 0, 130 ,255, 1);
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			SDL_RenderDrawPoint(e->render, x, y);
			x++;
		}
		y++;
		if (y == WIN_Y / 2)
			SDL_SetRenderDrawColor(e->render, 255, 0, 120, 1);
	}
}