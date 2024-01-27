/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:30:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/27 17:24:00 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	find_path_pos(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	return (-1);
}

char	*find_cmd(char **all_dir, char *cmd)
{
	char	*path;
	char	*slash_cmd;
	int		i;

	i = -1;
	while (all_dir[++i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		path = ft_strjoin(all_dir[i], slash_cmd);
		free(slash_cmd);
		if (access(path, X_OK) == 0)
		{
			free_mtx(all_dir);
			return (path);
		}
		free(path);
	}
	return (0);
}

char	*find_path(char *cmd, char **env)
{
	char	**all_dir;
	char	*path;
	int		pos;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pos = find_path_pos(env);
	if (pos < 0)
		return (NULL);
	all_dir = ft_split(env[pos] + 5, ':');
	path = find_cmd(all_dir, cmd);
	if (path)
		return (path);
	free_mtx(all_dir);
	return (0);
}

void	ft_execve(t_token *tokens, t_data *data, int fdin, int fdout)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		exec_exit_error(1, NULL);
		return ;
	}
	if (pid == 0)
	{
		printf("token en execve es %s\n", tokens->args[0]);
		path = find_path(tokens->args[0], data->envi);
		if (!path)
		{
			exec_exit_error(2, *tokens->args);
			exit(g_exit_code);
		}
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		if (execve(path, tokens->args, data->envi) == -1)
		{
			if (path && !tokens->next)
			{
				exec_exit_error(3, tokens->args[0]);
				exit(g_exit_code);
			}
			free_data(data);
		}
		free_data(data);
	}
	else
		signal_wait(pid);
}

void	process_cmd(t_token *tokens, t_data *data, int fdin, int fdout)
{
	if (!builtin(tokens->args[0], tokens, data, fdout))
		ft_execve(tokens, data, fdin, fdout);
}
