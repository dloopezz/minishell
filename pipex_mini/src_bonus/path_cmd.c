/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:05:36 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/15 16:21:38 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/**
 * It takes a command and an environment, and returns the path to the 
 * command if it exists, or the command itself if it doesn't
 * 
 * @param cmd the command to be executed
 * @param env the environment variables
 * 
 * @return The path to the executable file.
 */
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			double_pointer_free(s_cmd);
			return (exec);
		}
		free(exec);
	}
	double_pointer_free(allpath);
	double_pointer_free(s_cmd);
	return (cmd);
}

/**
 * It takes a command, splits it into an array of strings, gets the path of the
 * command, and executes it
 * 
 * @param path the path to the executable
 * @param cmd the command to execute
 * @param envp the environment variables
 */
void	exec(char *cmd, char **envp)
{
	char	**s_cmd = NULL;
	char	*path_cmd = NULL;

	if (access(cmd,X_OK) == 0)
	{
		path_cmd = get_path(s_cmd[0], envp);
	}
	if (!*envp)
		exit_error(8, *envp, 127);
	s_cmd = ft_split(cmd, ' ');
	path_cmd = get_path(s_cmd[0], envp);
	if (execve(path_cmd, s_cmd, envp) == -1)
	{
		double_pointer_free(s_cmd);
		exit (errno);
	}
}
