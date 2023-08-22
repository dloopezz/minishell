# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:55:52 by crtorres          #+#    #+#              #
#    Updated: 2023/08/22 16:55:39 by dlopez-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

LIB = includes/minishell.h

SRC = execute/main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "compiling minishell..."
	@$(CC) $(CFLAGS) $(OBJ) -I $(LIB) -o $(NAME) $(LDFLAGS)
	@echo "minishell compiled!!"

clean:
	@echo "cleaning everything..."
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re