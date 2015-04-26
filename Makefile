# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvolonda <jvolonda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/21 19:14:13 by jvolonda          #+#    #+#              #
#    Updated: 2015/04/25 18:02:18 by jvolonda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= wolf

SRC 		= main.c tools.c draw.c event.c raycast.c\

OBJ			= $(SRC:.c=.o)

CC			= gcc

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra

SDL_2_CFLAGS= $(shell sdl2-config --cflags)
SDL_2_LIBS= $(shell sdl2-config --libs)

all		: $(NAME)
	
$(NAME)	:
#	@make -C ./libft re
	@$(CC) $(CFLAGS) -c -I ./inc -I ./libft/includes $(SDL_2_CFLAGS) $(SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lft $(SDL_2_LIBS) -o $(NAME)
	@echo Compilation Done

clean	:
		@$(RM) $(OBJ)

fclean	:	clean
		@$(RM) $(NAME)

re		: fclean all
