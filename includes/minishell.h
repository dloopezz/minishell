/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:02:29 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/18 16:05:53 by crtorres         ###   ########.fr       */
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
# include <stdbool.h>
# include <fcntl.h>
# include <ctype.h>
# include "pipex.h"

# include "functions.h"

# define CMD 0
# define PIPE 1
# define LT 2
# define LLT 3
# define GT 4
# define GGT 5

# define TRUE 1
# define FALSE 0

typedef struct s_token    //para usar listas en parseo
{
	char			*data;
	int				type;
	char			**args;
	struct s_token	*next;
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

typedef struct s_cmd  //igual que token
{
	char	*cmd;
	int		*redir;
	char	**tab;
	char	**files;
}	t_cmd;

typedef struct s_data
{
	char	**env_copy;
	char	*var_name;
	char	*var_value;
	char	**path;
	char	**envi;
	char	**cmd;
	int		nbcmd;
	int		outfile;
	int		infile;
	int		prev_pipe;
	int		here_doc;
	int		*pid;
	char	**tab;
	int		fd[2];
	int		fddup[2];
	t_here	*here;
	t_cmd	cmds;
	int		nbhere;
	bool	stop;
	int		bool_s;
	int		bool_d;
	int		status;
	t_cmd	onecmd;
}	t_data;

//estan aqui pq no me detecta el t_token
t_token	*ft_parsing(char *line, t_token *tokens);
t_token	*add_token(t_token *cmd_lst, char *cmd, int type);
void	read_list(t_token *cmd_lst);
int	    ft_builtin(t_token *tokens, t_data *data);
int 	ft_cd(t_token *token, char **env);
int 	ft_listsize(t_token *lst);
int		ft_echo(t_token *token);
int		ft_env(t_data *data, t_token *tokens);
int 	ft_export(t_token *token, t_data *data);
void 	ft_execute(t_token *tokens, t_data *data);
//void	pipex(t_token *tokens, t_data *data);
//void	first_son(int *end, t_token *token, t_data *data);
//void	last_son(int *end, t_token *token, t_data *data);
 
#endif