/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/05 14:26:18 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	find_path(char *cmd, t_data *data)
{
	char	**all_dir;
	char	*slash_cmd;
	int		pos;
	int		i;

	 if (access(cmd, X_OK) == 0)
		return (cmd); 
	pos = find_path_pos(data->envi);
	all_dir = ft_split(data->envi[pos] + 5, ':');
	i = -1;
	while (all_dir[++i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		data->path = ft_strjoin(all_dir[i], slash_cmd);
		free(slash_cmd);
		if (access(data->path, X_OK) == 0)
		{
			free_mtx(all_dir);
			return ;
		}
		free(data->path);
	}
	free_mtx(all_dir);
} */

int	open_file(char *file, int type)
{
	int	fd_ret;

	if (type == 0)
		fd_ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ret == -1)
		exit(0);
	return (fd_ret);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	return (pid);
}

void	ft_executer(t_token *token, t_data *data, int fd_inf, int fd_outf)
{
	data->id = ft_fork();
	if (data->id == 0)
	{
		sig_child();
		check_infile(token, fd_inf);
		check_outfile(token, fd_outf);
		if (token->next)
			close(data->fd[READ]);
		if (execve(token->path, token->args, data->envi) == -1)
			exit(1);
	}
}

int	ft_exec_pipes(t_token *token, t_data *data, int st_fd)
{
	pipe(data->fd);
	if (data->fd < 0)
		exit (EXIT_FAILURE);
	ft_executer(token, data, st_fd, data->fd[WRITE]);
	close(data->fd[WRITE]);
	if (st_fd != STDIN_FILENO)
		close(st_fd);
	dup2(data->fd[READ], STDIN_FILENO);
	close(data->fd[READ]);
	return (data->fd[READ]);
}
void 	ft_exec(t_token *token, t_data *data)
{
	int	status;
	data->id = 0;
	t_token *tmp = token;
	int	fd_prueba;
	ft_check_cmd_path(tmp, data);			//?aqui hay que hacer la revision del PATH solo para los token que sean comandos
	/* while (tmp)
	{
		printf("path es [%s]\n", tmp->path);
		tmp = tmp->next;
	} */
	ft_here_doc(tmp, data);
	fd_prueba = STDIN_FILENO;
	while (tmp)
	{
		if (ft_is_builtin(tmp) == 0)
			fd_prueba = ft_builtin(tmp, data);
		else if (!tmp->next)
			ft_executer(tmp, data, fd_prueba, STDOUT_FILENO);
		else
			fd_prueba = ft_exec_pipes(tmp, data, fd_prueba);
		tmp = tmp->next;
	}
	if (fd_prueba != STDIN_FILENO)
		close(fd_prueba);
	sig_ignore();
	while (token->next)
		token = token->next;
	printf("token es [%s]\n", *token->args);
	if (data->id && data->id > 0)
	{
		waitpid(data->id, &status, 0);
		if (WIFSIGNALED(status))
		{
			waitpid(data->id, &status, 0);
			if (WTERMSIG(status) == 3)
				write(1, "Quit: 3", 7);
		}
	}
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	}
	sig_parent();
}

/* void	ft_execute(t_token *token, t_data *data)
{
	pid_t	id = 0;
	int	status;
	t_token *tmp = token;

	ft_here_doc(token, data);
	if (!token->next)
	{
		exec_one_cmd(token, data->envi);
		return ;
	}
	while (token->next)
	{
		pipe(data->fd);
		if (data->fd < 0)
			exit (EXIT_FAILURE);
			
		id = fork();
		if (id < 0)
			exit(EXIT_FAILURE);	
			
		if (id == 0)
		{
			if (token->next && token->next->type == PIPE)
			{
				dup2(data->fd[1], STDOUT_FILENO);
				close(data->fd[1]);
			}
			else if (token->next && token->next->type == GT)
			{
				data->outfile = open_file(token->next->next->args[0], 1);
				dup2(data->outfile, STDOUT_FILENO);
				close(data->outfile);
			}
			else if (token->next && token->next->type == GGT)
			{
				data->outfile = open_file(token->next->next->args[0], 2);
				dup2(data->outfile, STDOUT_FILENO);
				close(data->outfile);
			}
			else if (token->next && token->next->type == LT)
			{
				data->infile = open_file(token->next->next->args[0], 0);
				dup2(data->infile, STDIN_FILENO);
				close(data->infile);
			}
			else if (token->next && token->next->type == LLT)
			{
				data->infile = open_file(*token->next->next->args, 0);
				dup2(data->heredc->fd[1], STDIN_FILENO);
				close(data->heredc->fd[1]);
			}
			exec_cmd(tmp, data->envi);
		}
		else
		{
			if (token->next && token->next->type == PIPE)
			{
				tmp = tmp->next;
				close(data->fd[1]);
				dup2(data->fd[0], STDIN_FILENO);
				waitpid(id, 0, 0);
			}
			if (token->next && (token->next->type == LT || token->next->type == LLT || token->next->type == GT || token->next->type == PIPE))
				token = token->next->next;
			else
				token = token->next;
		}
	}
	if (token->prev && token->prev->type == PIPE)
		exec_one_cmd(token, data->envi);
	dup2(STDOUT_FILENO, STDIN_FILENO);
	waitpid(id, &status, 0);
} */
			// sig_child();
			// if (WIFSIGNALED(status))
			// {
			// 	waitpid(id, &status, 0);
			// 	if (WTERMSIG(status) == 3)
			// 		write(1, "Quit: 3", 7);
			// }
		// if (token->prev && token->prev->type == PIPE) //parece que no hace nada pero debería estar
		// {	
		// 	close(data->fd[0]);
		// 	close(data->fd[1]);
		// }