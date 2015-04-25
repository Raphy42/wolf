/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvolonda <jvolonda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:41:50 by jvolonda          #+#    #+#             */
/*   Updated: 2015/04/25 16:29:08 by jvolonda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdio.h>
#include "wolf.h"

int main(void) {

    SDL_Window *window;
    SDL_Event event;
    SDL_Renderer *render;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow( "wolf3d",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (window == NULL) 
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    draw(e, )
    while(1)
    {
        while(SDL_PollEvent(&event))
        {
          if (event.type == SDL_KEYDOWN)
          {
              if (event.key.keysym.sym == 27)
              { 
                  SDL_DestroyWindow(window);
                  SDL_Quit();
                  exit(1);
              }
              if (event.key.keysym.sym == LEFT)
              { 
                x--;
                  SDL_RenderDrawPoint(render, x, y);
                   SDL_RenderPresent(render);
              }
              if (event.key.keysym.sym == UP)
              { 
                y--;
                  SDL_RenderDrawPoint(render, x, y);
                   SDL_RenderPresent(render);
                }
              if (event.key.keysym.sym == DOWN)
              { 
                y++;
                  SDL_RenderDrawPoint(render, x, y);
                  SDL_RenderPresent(render);
              }
              if (event.key.keysym.sym == RIGHT)
              { 
                x++;
                  SDL_RenderDrawPoint(render, x, y);
                  SDL_RenderPresent(render);
              }
               printf("%d\n",event.key.keysym.sym);
          }
        }
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}