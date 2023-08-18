# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:55:52 by crtorres          #+#    #+#              #
#    Updated: 2023/08/14 18:01:09 by crtorres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./src

INC = ./includes/

DOT_O = _objFiles

CC = gcc

CFLAGS =-Wall -Wextra -Werror -g3 -fsanitize=thread

SRC =  \

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJS = $(addprefix $(DOT_O)/, $(SRC:%.c=%.o))

all: $(NAME) $(DOT_O)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(GREEN) "\n👍🏽philosophers succesfully compiled!👍🏽\n " $(RESET)

$(DOT_O):
	@mkdir -p $(DOT_O)

$(DOT_O)/%.o: $(SRC_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING PHILOSOPHERS... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(PURPLE) "\n" CLEANING... $(RESET)
	@rm -f $(OBJS)
	@rm -rf $(DOT_O)
	$(GREEN) "CLEAN COMPLETE\n" $(RESET)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make -s all

# *COLORS *#
#
GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m"
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
YELLOW = \033[0;93m
RESET 	= "\033[1;0m"

.PHONY: all clean fclean re