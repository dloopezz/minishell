/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:36:23 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/24 15:58:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_pipes(t_token *tokens)
{
	t_token	*aux;
	int		n_pipes;

	aux = tokens;
	n_pipes = 0;
	while (aux->next)
	{
		if (aux->type == PIPE)
			n_pipes++;
		aux = aux->next;
	}
	return (n_pipes);
}

int	open_file(char *file, int type)
{
	int	fd_ret;
	
	if (strlen(file) > sizeof(file))
        return (-1);
	if (type == 0)
		fd_ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ret == -1)
	{
		perror("error opening file\n");
		exit(EXIT_FAILURE);
	}
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
		check_infile(token, data, fd_inf);
		check_outfile(token, data, fd_outf);
		//printf("REGRESA\n");
		if (token->next && token->next->type == CMD)
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
	return (data->fd[READ]);
}

t_token	*copyWithoutPipe(t_token *token)
{
	t_token	*new_head = NULL;
	t_token	*struct_cpy = token;
	t_token	*current_new = NULL;

	while (struct_cpy != NULL)
	{
		if (struct_cpy->type != PIPE)
		{
			t_token* new_node = (t_token*)malloc(sizeof(t_token));
			if (new_node == NULL)
				return (NULL);
			new_node->args = struct_cpy->args;
			new_node->type = struct_cpy->type;
			new_node->redir = struct_cpy->redir;
			new_node->path = struct_cpy->path;
			new_node->next = NULL;
			if (new_head == NULL)
			{
				new_head = new_node;
				current_new = new_node;
			}
			else
			{
				current_new->next = new_node;
				new_node->prev = current_new;
				current_new = new_node;
			}
		}
		struct_cpy = struct_cpy->next;
	}
	return (new_head);
}

/* int	ft_exec_heredoc(t_token *token, t_data *data)
{
	int	fd[2];
	
	pipe(fd);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if(!ft_fork())
	{
		close(fd[READ]);
		//printf("outf en exec_builtins es %s\n", token->outf);
		if (data->outfile != NULL)
			check_outfile(token, data, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		handle_heredoc(data, STDIN_FILENO);
		exit(0);
	}
	close(fd[WRITE]);
	return (fd[READ]);
} */

void	ft_check_redir(t_token *token, t_data *data)
{
	int	file;
	
	t_token *tmp = token;
	data->infile = ft_calloc(sizeof(t_data), 1);
	/* if (!data->outfile)
		return ; */
	//printf("mem de outfile es %p en línea 152\n", data->outfile);
	//printf("mem de infile es %p en línea 152\n", data->infile);
	while (tmp)
	{
		//printf("entra en check redir y outf es %p\n", (data)->outfile[0]);
		//printf("(tmp) en redir es %s\n", (tmp)->args[0]);
		if (is_redir((tmp)->type))
		{
			if ((tmp)->type == GT || (tmp)->type == GGT)
			{
				if ((tmp)->type == GT)
					file = open_file(*(tmp)->next->args, 1);
				else if ((tmp)->type == GGT)
					file = open_file(*(tmp)->next->args, 2);
				close(file);
			}
			else if ((tmp)->type == LT || (tmp)->type == LLT)
			{
				if ((tmp)->type == LT)
				{
					if (tmp->next->type == INFILE)
						(data)->infile = (tmp)->next->args[0];
					if (access(data->infile, F_OK) == -1)
						exec_exit_error(5, "No such file or directory");
				}
				else if (tmp->type == LLT)
					data->del = tmp->next->args;
			}
		}
		if (tmp->type == INFILE)
			(data)->infile = (tmp)->args[0];
		//printf("(tmp) type en redir es %d\n", (tmp)->type);
		if ((tmp)->type == OUTFILE)
		{
			(data)->outfile = ft_calloc(sizeof(t_data), 1);
			//printf("entra\n");
			if (data->outfile)
			{
				free(data->outfile);
				data->outfile = NULL;
				(data)->outfile = (tmp)->args[0];
			}
		}
		//printf("entra en check redir data es %s\n", data->outf[0]);
		//printf("entra en check redir tmp dir es %p\n", tmp);
		//tmp = NULL;
		(tmp) = (tmp)->next;
	}
	//free(tmp);
}


void 	ft_exec(t_token *token, t_data *data)
{
	int	status;
	data->id = 0;
	t_token *tmp = copyWithoutPipe(token);
	t_token *first = tmp;
	int	fd_prueba;
	int	n_pipes = get_pipes(token);
	int	i = -1;
	
	ft_check_cmd_path(tmp, data);
	ft_check_redir(tmp, data);
	//prueba_heredoc();
	
	//*PARA LIBERAR Y NO FUNCIONA!!
	/* while (tmp)
	{
		printf("args es dir es %p\n", tmp);
		free (tmp);
		tmp = tmp->next;
	} */

	if (data->del != NULL)
		ft_here_doc(tmp, data);
	//!printf("del es %s\n", data->del[0]);  BORRAR
	tmp = first;
	//if (data->outfile)
    	//printf("outfile in exec is %s\n", data->outfile);
	//ft_exec_heredoc(tmp, data);
	fd_prueba = STDIN_FILENO;
	/* if (data->del != NULL)
	{
		printf("entra en la mierda\n");
		fd_prueba = data->heredc->fd[0];
	} */
	while (tmp && ++i <= n_pipes)
	{
		//printf("token en bucle es %s\n", *tmp->args);
		if (ft_is_builtin(tmp) == 0){
			fd_prueba = prueba_builtin(tmp, data);
			//printf("fd_prueba es [%d]\n", fd_prueba);
		}
		else if (i == n_pipes)
		{
			printf(RED"entra en else if\n"RESET);
			//printf("token tmp es %s\n", *tmp->args);
			ft_executer(tmp, data, fd_prueba, STDOUT_FILENO);
		}
		else
		{
			printf(BLUE"entra en else\n"RESET);
			fd_prueba = ft_exec_pipes(tmp, data, fd_prueba);
		}
		tmp = tmp->next;
	}
	data->del = NULL;
	/* if (data->outfile != NULL)
	{
		printf("mem de outfile es %p en línea 262\n", data->outfile);
		free (data->outfile);
		data->outfile = NULL;
	} */		
	//free(tmp);
	if (fd_prueba != STDIN_FILENO)
		close(fd_prueba);
	sig_ignore();
	while (token->next)
		token = token->next;
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
	if (data->file_hd)
	{
		if (access(data->file_hd, F_OK) != -1)
			unlink(data->file_hd);
		free(data->file_hd);
	}
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