/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:02:29 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/31 17:35:54 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# include "pipex.h"

# include "functions.h"

# define CMD 0
# define PIPE 1
# define LT 2
# define LLT 3
# define GT 4
# define GGT 5
# define FILE 6

# define TRUE 1
# define FALSE 0

# define SINGLE_QUOTES 39
# define DOUBLE_QUOTES 34

# define UNQUOTED 0
# define QUOTED 1

typedef struct s_token
{
	char			**args;
	int				type;
	int				*redir;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_here
{
	char	*delim;
	int		fd[2];
}	t_here;

typedef struct s_env
{
	char	**env_copy;
	char	*var_name;
	char	*var_value;
}	t_env;


typedef struct s_data
{
	char	**env_copy;
	char	*var_name;
	char	*var_value;
	char	**path;
	char	**envi;
	char	**cmd;
	int		nbcmd;
	int		exit_code;
	int		outfile;
	int		infile;
	int		prev_pipe;
	int		here_doc;
	int		*pid;
	char	**tab;
	int		fd[2];
	int		fddup[2];
	t_here	*here;
	// t_cmd	cmds;
	int		nbhere;
	bool	stop;
	int		bool_s;
	int		bool_d;
	int		status;
	struct termios	termios;
	// t_cmd	onecmd;
	int				is_quoted;
}	t_data;

t_data	g_var;
 
#endif