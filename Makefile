NAME = minishell

SRC_PATH = ./execute
BUL_PATH = ./builtins
PAR_PATH = ./parsing
ERR_PATH = ./error_message

DOT_O = _objFiles

CC = gcc
CFLAGS = -I/Users/$(USER)/.brew/opt/readline/include -Wall -Werror -Wextra -fsanitize=address -g3
LIBFT = ./libft/libft.a
LDFLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
#READLINE_LIB= -L $(shell brew --prefix readline)/lib/ -lreadline -L . $(LIBFT)
READLINE_HEADER= -I . -I$(shell brew --prefix readline)/include/ -I include/

LIB = includes/minishell.h

SRC =	main.c\
		execute.c\
		expand.c\
		expand_utils.c\
		here_doc.c\
		ft_builtin.c\
		ft_cd.c\
		ft_echo.c\
		ft_export.c\
		ft_exit.c\
		ft_pwd.c\
		ft_unset.c\
		ft_builtins_utils.c\
		ft_builtin_utils2.c\
		ft_builtin_utils3.c\
		ft_env.c\
		parsing.c\
		modes.c\
		redirs.c\
		utils.c\
		error_msg.c\
		pipex.c\
		pipex_utils.c\
		signals.c\
		exec_path.c\
		exec_utils.c\
		token_utils.c\
		
OBJ = $(addprefix $(DOT_O)/, $(SRC:%.c=%.o))

all: make_libft $(DOT_O) $(NAME)

$(DOT_O):
	@mkdir -p $(DOT_O)

$(DOT_O)/%.o: $(SRC_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@

$(DOT_O)/%.o: $(BUL_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@

$(DOT_O)/%.o: $(PAR_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@

$(DOT_O)/%.o: $(ERR_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@
	
make_libft:
	@make all -sC ./libft
	
$(NAME): $(OBJ)
	@clear
	@echo $(GREEN)
	@clear
	@echo "C"
	@sleep 0.05
	@clear
	@echo "CO"
	@sleep 0.05
	@clear
	@echo "COM"
	@sleep 0.05
	@clear
	@echo "COMP"
	@sleep 0.05
	@clear
	@echo "COMPI"
	@sleep 0.05
	@clear
	@echo "COMPIL"
	@sleep 0.05
	@clear
	@echo "COMPILI"
	@sleep 0.05
	@clear
	@echo "COMPILIN"
	@sleep 0.05
	@clear
	@echo "COMPILING"
	@sleep 0.05
	@clear
	@echo "COMPILING M"
	@sleep 0.05
	@clear
	@echo "COMPILING MI"
	@sleep 0.05
	@clear
	@echo "COMPILING MIN"
	@sleep 0.05
	@clear
	@echo "COMPILING MINI"
	@sleep 0.05
	@clear
	@echo "COMPILING MINIS"
	@sleep 0.05
	@clear
	@echo "COMPILING MINISH"
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHE"
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHEL"
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHELL"
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHELL."
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHELL.."
	@sleep 0.05
	@clear
	@echo "COMPILING MINISHELL..."
	@sleep 0.1
	@$(CC) $(CFLAGS) $(READLINE_HEADER) $(LIBFT) $(OBJ) -I $(LIB) -o $(NAME)  $(LDFLAGS)
	
	@clear
	@echo "--------------------------"
	@echo "|                        |"
	@echo "| READY TO USE MINISHELL |"
	@echo "|                        |"
	@echo "--------------------------"
	
	@echo $(RESET)
	
#quitar esto a la hora de  entregar
#	@./minishell

##$(READLINE_LIB)$(READLINE_HEADER)


clean:
	$(CYAN) "\n cleaning everything...\n" $(RESET)
	@rm -f $(OBJ)
	@make clean -sC ./libft
	@rm -rf $(DOT_O)

fclean: clean
	@clear
	@rm -f $(NAME)
	@make fclean -sC ./libft
	@rm -rf $(DOT_O)

re: fclean all

GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m"
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
YELLOW = \033[0;93m
RESET 	= "\033[1;0m"

.PHONY: all clean fclean re
