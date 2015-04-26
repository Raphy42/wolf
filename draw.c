#include "wolf.h"

void	draw_base(t_wolf *e)
{
	int	x;
	int	y;

	y = 0;
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