# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/21 19:14:13 by mrbanane          #+#    #+#              #
#    Updated: 2015/06/03 17:10:42 by rdantzer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= wolf3d

SRC= main.c events.c parse.c draw.c tools.c sprite.c hud.c sprite_render.c\
	sprite_sort.c color.c floor_cast.c shadows.c keys.c ray_cast.c\
	minimap.c

OBJ= $(SRC:.c=.o)

CC= gcc
RM= rm -rf

CFLAGS= -Wall -Werror -Wextra -O3

SDL_2_CFLAGS= $(shell sdl2-config --cflags)
SDL_2_LIBS= $(shell sdl2-config --libs)

## Aesthetics
RED= \033[34m
GREEN= \033[32m
RESET= \033[0m

all: $(NAME)
	
$(NAME):
	@make -C ./libft
	@printf "$(RED)[WOLF3D] Compiling sources...$(RESET)\t\t"
	@$(CC) $(CFLAGS) -c -I ./inc -I ./libft/includes $(SDL_2_CFLAGS) $(SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lft $(SDL_2_LIBS) -o $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"

clean:
	@printf "$(RED)[WOLF3D] Removing objects...$(RESET)\t\t"
	@$(RM) $(OBJ)
	@printf "$(GREEN)Done$(RESET)\n"

fclean:	clean
	@printf "$(RED)[WOLF3D] Removing wolf3d...$(RESET)\t\t"
	@$(RM) $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"

re: fclean all
