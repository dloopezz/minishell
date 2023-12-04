/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/04 12:52:57 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
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

void	find_path(char *cmd, t_data *data)
{
	char	**all_dir;
	char	*slash_cmd;
	int		pos;
	int		i;

	/* if (access(cmd, X_OK) == 0)
		return (cmd); */
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
}

char	*find_in_path(char *cmd, char **env)
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

	//ft_putendl_fd(*token->args, 2);
	//ft_putendl_fd(*prueba_cmd, 2);
	path = find_in_path(token->args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	if (execve(path, &token->args[0], env) == -1)
		exit (1);
}

void	exec_one_cmd(t_token *token, char **env)
{
	pid_t	id = 0;
	int	status;
	
	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		sig_child();
		if (WIFSIGNALED(status))
			waitpid(id, &status, 0);
				if (WTERMSIG(status) == 3)
					write(1, "Quit: 3", 7);
		exec_cmd(token, env);
	}
	waitpid(id, &status, 0);
}

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

void 	ft_check_cmd_path(t_token *token, t_data *data)
{
	t_token	*tmp = token;
	
	while (tmp)
	{
		if (ft_is_builtin(tmp) == 0)
			return;
		else if (tmp->args && tmp->type == CMD && tmp->args[0])
		{
			if (access(tmp->args[0],X_OK) != 0)
				find_path(tmp->args[0], data);
		}
		else
			data->path = ft_strdup(tmp->args[0]);
		tmp = tmp->next;
	}
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
			close(data->fd[0]);
			printf("path es %s\n", data->path);
			printf("token es %s\n", *token->args);
		if (execve(data->path, token->args, data->envi) == -1)
			exit(1);
	}
}

int	ft_exec_pipes(t_token *token, t_data *data, int fd_out)
{
	pipe(data->fd);
	if (data->fd < 0)
		exit (EXIT_FAILURE);
	ft_executer(token, data, fd_out, data->fd[1]);
	close(data->fd[1]);
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	return (data->fd[0]);
}
void 	ft_exec(t_token *token, t_data *data)
{
	int	status;
	data->id = 0;
	t_token *tmp = token;
	int	fd_prueba = STDIN_FILENO;
	ft_check_cmd_path(token, data);			//?aqui hay que hacer la revision del PATH solo para los token que sean comandos
	//printf("path es %s\n", data->path);
	ft_here_doc(tmp, data);
	while (tmp)
	{
		if (ft_is_builtin(tmp) == 0)
			fd_prueba = ft_builtin(tmp, data);
		else if (!tmp->next){
			printf("TMP: |%s|\n", tmp->args[0]);
			ft_executer(tmp, data, fd_prueba, STDOUT_FILENO);
		}
		//	exec_one_cmd(tmp, data->envi);
		else
		{
			printf("TMP: |%s|\n", tmp->args[0]);
			fd_prueba = ft_exec_pipes(tmp, data, fd_prueba);
		}
		tmp = tmp->next;
	}
	if (fd_prueba != STDIN_FILENO)
		close(fd_prueba);
	sig_ignore();
	/* while (tmp->next)
		tmp = tmp->next; */
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
		if (waitpid(-1, &status, 0) == -1)
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