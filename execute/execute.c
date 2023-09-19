/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/19 17:02:15 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_msg("|path not found| ");
	exit (1);
}

char	*find_path(char *cmd, char **env)
{
	char	**all_dir;
	char	*slash_cmd;
	char	*path;
	int		pos;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pos = find_path_pos(env);
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

void	exec_cmd(t_token *token, char **env)
{
	char	*path;

	path = find_path(token->args[0], env);
	if (!path)
	{
		ft_putstr_fd("|command not found| ", 2);
		exit (127);
	}
	if (execve(path, token->args, env) == -1)
		exit (1);
} */

void ft_execute(t_token *token, t_data *data)
{
	pid_t	id;
	int	status;

	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
		exec_cmd(token, data->envi);
	// pipex(tokens, data->envi);
	waitpid(id, &status, 0);
}
