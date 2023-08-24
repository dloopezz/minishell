# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:55:52 by crtorres          #+#    #+#              #
#    Updated: 2023/08/24 15:42:26 by dlopez-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

LIBFT = ./libft/libft.a
LIB = includes/minishell.h

SRC =	execute/main.c\
		parsing/parsing.c\
		
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