/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:57:33 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 15:04:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipe
{
	char	**path;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	int		status;
}	t_pipe;

int		main(int argc, char **argv, char **envp);
void	double_pointer_free(char **ptr);
char	*checkcommand_in_path(char **path, char *command);
void	exit_error(int err, char *msg, int errcode);

#endif