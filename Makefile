# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:55:52 by crtorres          #+#    #+#              #
#    Updated: 2023/09/08 00:00:39 by lopezz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

LIBFT = ./libft/libft.a
LIB = includes/minishell.h

SRC =	execute/main.c\
		parsing/parsing.c\
		parsing/utils.c\
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling libft..."
	@make all -sC ./libft
	@$(CC) $(CFLAGS) $(OBJ) -I $(LIB) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "compiling minishell..."
	@echo "minishell compiled!!"

clean:
	@echo "cleaning everything..."
	@rm -f $(OBJ)
	@make clean -sC ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC ./libft

re: fclean all

.PHONY: all clean fclean re
