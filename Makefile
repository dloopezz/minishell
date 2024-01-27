
NAME = minishell

SRC_PATH = ./src/execute
BUL_PATH = ./src/builtins
PAR_PATH = ./src/parsing
ERR_PATH = ./src/error_message
EXPAND_PATH = ./src/expand

DOT_O = _objFiles

CC = gcc
CFLAGS = -I/Users/$(USER)/.brew/opt/readline/include -Wall -Werror -Wextra -g3 -fsanitize=address -g3
#-I/Users/$(USER)/.brew/opt/readline/include
LIBFT = ./src/libft/libft.a
#READLINE_LIB= -L $(shell brew --prefix readline)/lib/ -lreadline -L . $(LIBFT)

######?Para Mac 42###############
LDFLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
READLINE_HEADER= -I . -I$(shell brew --prefix readline)/include/ -I include/

######?Para portatil###############
#RLINE_INC_2   = -I . -I/usr/local/Cellar/readline/8.2.7/include
#RLINE_L_2     = -lreadline -L/usr/local/Cellar/readline/8.2.7/lib


LIB = includes/minishell.h

SRC =	minishell.c\
		expand.c\
		expand_utils.c\
		ft_cd.c\
		ft_echo.c\
		ft_export.c\
		ft_exit.c\
		ft_pwd.c\
		ft_unset.c\
		utils1_builtin.c\
		utils2_builtin.c\
		utils3_builtin.c\
		utils4_builtin.c\
		ft_env.c\
		parsing.c\
		modes.c\
		utils_parsing.c\
		error_msg.c\
		error_msg2.c\
		utils_token.c\
		utils2_token.c\
		exit.c\
		reorder.c\
		reorder_cases.c\
		signals.c\
		exec_path.c\
		execute.c\
		here_doc.c\
		exec_utils.c\
		utils_exec2.c\
		utils_exec.c\
		#exec.c\
		cmd.c\
		redir.c\
		exec_prueba.c\
		
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

$(DOT_O)/%.o: $(EXPAND_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(READLINE_HEADER) -c $< -o $@
	
make_libft:
	@make all -sC ./src/libft
	
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(READLINE_HEADER) $(LIBFT) $(OBJ) -I $(LIB) -o $(NAME) $(LDFLAGS)
	$(GREEN)
	@clear
	@echo "READY TO USE MINISHELL"
	
	@echo $(RESET)
	
#quitar esto a la hora de  entregar
#	@./minishell

##$(READLINE_LIB)$(READLINE_HEADER)


clean:
	$(CYAN) "\n cleaning everything...\n" $(RESET)
	@rm -f $(OBJ)
	@make clean -sC ./src/libft
	@rm -rf $(DOT_O)

fclean: clean
	@clear
	@rm -f $(NAME)
	@make fclean -sC ./src/libft
	@rm -rf $(DOT_O)

re: fclean all

GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m"
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
YELLOW = \033[0;93m
RESET 	= "\033[1;0m"

.PHONY: all clean fclean re