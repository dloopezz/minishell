/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:57:33 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 15:04:45 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../../libft/libft.h"
# include <errno.h>

# define ARG_ERR 1
# define PIPE_ERR 2
# define FORK_ERR 3
# define NO_INFILE 4
# define NO_OUTFILE 5
# define COM_ERR 6
# define ERR_HEREDOC 7

typedef struct s_pipe
{
	char	**path;
	char	**cmd;
	int		fd_pipe[2];
	pid_t	*pid;
	int		here_doc;
	int		max_cmd;
	int		pipe_nb;
	int		fd_in;
	int		fd_out;
	int		fd_read;
	int		fd_write;
	int		i;
	int		cmd_i;
	int		status;
}	t_pipe;

int		main(int argc, char **argv, char **envp);
void	double_pointer_free(char **ptr);
char	*checkcommand_in_path(char **path, char *command);
int		open_file(char *file, int type);
void	exit_error(int err, char *msg, int errcode);
void	exec(char *cmd, char **envp);
void	here_doc(char **argv);
char	*my_env(char *name, char **envp);

#endif