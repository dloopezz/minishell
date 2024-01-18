/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:02:29 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/18 16:56:05 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdbool.h>
# include <fcntl.h>
# include <ctype.h>
# include <signal.h>

# include "functions.h"

# define CMD 0
# define PIPE 1
# define LT 2
# define LLT 3
# define GT 4
# define GGT 5
# define INFILE 6
# define OUTFILE 7
# define DELM 8

# define TRUE 1
# define FALSE 0

# define SQUOTES 39
# define DQUOTES 34

# define UNQUOTED 0
# define QUOTED 1

# define READ 0
# define WRITE 1

typedef struct s_token
{
	char			**args;
	int				type;
	char			*redir;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_data
{
	char			*line;
	char			*l_exp;
	char			**envi;
	char			**env_cpy;
	t_token			*tokens;
	t_token			*token_aux;
	struct termios	termios;
}	t_data;

int	g_exit_code;

//*===SETTINGS COLORS===*/
//*===Color font code===*/
# define BLACK   "\x1B[30m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1B[37m"
# define ORANGE  "\x1B[38;2;255;128;0m"
# define ROSE    "\x1B[38;2;255;151;203m"
# define LBLUE   "\x1B[38;2;53;149;240m"
# define LGREEN  "\x1B[38;2;17;245;120m"
# define GRAY    "\x1B[38;2;176;174;174m"
//*===Color background code===*/
# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"
# define BG_ORANGE  "\x1B[48;2;255;128;0m"
# define BG_LBLUE   "\x1B[48;2;53;149;240m"
# define BG_LGREEN  "\x1B[48;2;17;245;120m"
# define BG_GRAY    "\x1B[48;2;176;174;174m"
# define BG_ROSE    "\x1B[48;2;255;151;203m"

# define RESET   "\x1b[0m"

#endif