# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 14:52:05 by crtorres          #+#    #+#              #
#    Updated: 2023/10/10 14:29:56 by crtorres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = ./srcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDE = libft.h
RM = rm -rf

DOT_O = _objFiles

SRC = 	ft_atoi.c\
		ft_atol.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strcpy.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strcmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		get_next_line.c\
		get_next_line_utils.c\
		

OBJS = $(addprefix $(DOT_O)/, $(SRC:%.c=%.o))

all: $(NAME) $(DOT_O)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(DOT_O):
	@mkdir -p $(DOT_O)

$(DOT_O)/%.o: $(SRC_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING LIBFT... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@$(RM) $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(DOT_O)

re: fclean

re: fclean all

GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m"
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
YELLOW = \033[0;93m
RESET 	= "\033[1;0m"

.PHONY: all re clean fclean