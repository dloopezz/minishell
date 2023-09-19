/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:56:23 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/18 18:19:05 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_found("|path not found| ");
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

void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = find_path(cmd_flags[0], env);
	if (!path)
	{
		ft_putstr_fd("|command not found| ", 2);
		exit (127);
	}
	if (execve(path, cmd_flags, env) == -1)
		exit (1);
}

void	first_son(int *end, t_token *token, t_data *data)
{
	pid_t	id;
	int		file1;
	char	*command1;

	command1 = token->args[0];
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		file1 = ft_open(token->args[1], INFILE);
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		dup2(file1, STDIN_FILENO);
		close(file1);
		ft_builtin(token, data);
		//exec_cmd(command1, env);
	}
}

void	last_son(int *end, t_token *token, t_data *data)
{
	pid_t	id;
	int		file2;
	char	*command2;

	command2 = token->args[0];
	printf("argv[0] es %s\n", token->args[0]);
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		file2 = ft_open(token->args[0], OUTFILE);
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		ft_builtin(token, data);
		//exec_cmd(command2, data);
	}
}

void	pipex(t_token *tokens, t_data **data)
{
	int		end[2];
	int		status;
	t_token *past_token;

	pipe(end);
	if (end < 0)
		exit (EXIT_FAILURE);
	printf("que es esto %s\n", tokens->args[0]);
	past_token = tokens;
	first_son(end, tokens, *data);
	past_token = tokens->next->next;
	printf("siguiente token %s\n", past_token->args[0]);
	last_son(end, past_token, *data);
	close(end[0]);
	close(end[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}
