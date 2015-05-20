# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/21 19:14:13 by mrbanane          #+#    #+#              #
#    Updated: 2015/05/20 09:08:04 by rdantzer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= wolf

SRC= main.c events.c parse.c draw.c tools.c sprite.c hud.c

OBJ= $(SRC:.c=.o)

CC= gcc
RM= rm -rf

CFLAGS= -Wall -Werror -Wextra -O3

SDL_2_CFLAGS= $(shell sdl2-config --cflags)
SDL_2_LIBS= $(shell sdl2-config --libs)

all: $(NAME)
	
$(NAME):
#	@make -C ./libft re
	@$(CC) $(CFLAGS) -c -I ./inc -I ./libft/includes $(SDL_2_CFLAGS) $(SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lft $(SDL_2_LIBS) -o $(NAME)
	@echo Compilation Done

clean:
		@$(RM) $(OBJ)

fclean:	clean
		@$(RM) $(NAME)

re: fclean all
