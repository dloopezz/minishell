# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:55:52 by crtorres          #+#    #+#              #
#    Updated: 2023/09/14 15:10:48 by crtorres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

LIBFT = ./libft/libft.a
LIB = includes/minishell.h

SRC =	execute/main.c\
		execute/execute.c\
		parsing/parsing.c\
		parsing/utils.c\
		builtins/ft_builtin.c\
		builtins/ft_cd.c\
		builtins/ft_echo.c\
		builtins/ft_export.c\
		builtins/ft_exit.c\
		builtins/ft_pwd.c\
		builtins/ft_unset.c\
		builtins/ft_builtins_utils.c\
		builtins/ft_builtin_utils2.c\
		builtins/ft_env.c\
		error_message/error_msg.c\
		
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
