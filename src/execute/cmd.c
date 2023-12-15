/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:30:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/15 13:05:04 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	builtin(char *cmd, t_token *tokens, t_data *data, int fd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(fd), 1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return(ft_cd(tokens, data->envi), 1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data, tokens, fd), 1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(tokens, data, fd), 1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(tokens, data), 1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(tokens, fd), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(tokens->args), 1);
	return (0);
}

int	find_path_pos2(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_msg("|path not found| ");
	exit (1);
}

char	*find_path2(char *cmd, char **env)
{
	char	**all_dir;
	char	*slash_cmd;
	char	*path;
	int		pos;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pos = find_path_pos2(env);
	all_dir = ft_split(env[pos] + 5, ':');
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
	free_mtx(all_dir);
	return (0);
}

void	ft_execve(t_token *tokens, t_data *data, int fdin, int fdout)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		path = find_path2(tokens->args[0], data->envi);
		if (!path)
		{
			ft_putstr_fd("cmd not found\n", 2);
			exit (127);
		}
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		if (execve(path, tokens->args, data->envi) == -1)
			exit(1);
	}
	else
		waitpid(pid, &status, 0);
}

void	process_cmd(t_token *tokens, t_data *data, int fdin, int fdout)
{
	if (!builtin(tokens->args[0], tokens, data, fdout))
		ft_execve(tokens, data, fdin, fdout);
}
