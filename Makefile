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

SRC 		= main.c tools.c\

OBJ			= $(SRC:.c=.o)

CC			= gcc

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra

FLAGS		= -L/nfs/zfs-student-5/users/2014/jvolonda/.brew/lib -lSDL2 -L./libft -lft

all		: $(NAME)
	
$(NAME)	:
#	@make -C ./libft re
	@$(CC) $(CFLAGS) -c -I ./inc -I ./libft/includes -I/nfs/zfs-student-5/users/2014/jvolonda/.brew/include/SDL2 -D_THREAD_SAFE $(SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lft $(FLAGS) -o $(NAME)
	@echo Compilation Done

clean	:
		@$(RM) $(OBJ)

fclean	:	clean
		@$(RM) $(NAME)

re		: fclean all
