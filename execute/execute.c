/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/28 17:16:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx(char **mtx)
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*token->args, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	if (execve(path, token->args, env) == -1)
		exit (1);
}
/* void	put_here_doc(t_token *token, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	line = readline("> ");
	while (line)
	{
		printf("line es |%s|\n", line);
		printf("token->next->args es |%s|\n", token->next->args[0]);
		printf("len de token->next->args es |%zu|\n", ft_strlen(*token->next->args));
		if ((ft_strncmp(line, *token->next->args, ft_strlen(*token->next->args) + 1) == 0)
			&& (ft_strlen(line) == ft_strlen(*token->next->args)))
		{
			free(line);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
}
void	init_here_doc(t_token *token)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		exit(0);
	while (token->next)
	{
		if (token->type && token->type == LLT)
		{
			pid = fork();
			if (pid == -1)
				exit (0);
			if (pid == 0)
			{
				sig_heredoc();
				put_here_doc(token, fd);
				//close(fd[1]);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				waitpid(pid, &status, 0);
				printf("llega\n");
			}
			sig_ignore();
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 2)
				{
					if (access(*token->next->args, F_OK) != -1)
					{
						fd[0] = open(*token->next->args, O_CREAT | O_WRONLY | O_TRUNC, 0644);
						close(fd[1]);
					}
				}
			}
			sig_parent();
		}
		token = token->next;
	}
} */

t_token *ft_execute(t_token *token, t_data *data)
{
	pid_t	id = 0;
	int	status;
	
	ft_here_doc(token, data);
	exit (0);
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		sig_child();
		if (WIFSIGNALED(status))
		{
			waitpid(id, &status, 0);
			if (WTERMSIG(status) == 3)
				write(1, "Quit: 3", 7);
		}
		
		if (token->next && token->next->type == GT)
		{
			int outfile = open(token->next->next->args[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(outfile, STDOUT_FILENO);
		}
		if (token->next && token->next->type == LT)
		{
			int infile = open(token->next->next->args[0], O_RDONLY, 0644);
			dup2(infile, STDIN_FILENO);
		}
		exec_cmd(token, data->envi);
	}
	if (token->next && (token->next->type == LT || token->next->type == GT))
		token = token->next->next;

	// pipex(tokens, data->envi);
	waitpid(id, &status, 0);
	return (token);
}
