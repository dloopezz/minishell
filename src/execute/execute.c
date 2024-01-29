/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:36:23 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/29 13:02:55 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_executer(t_token *token, t_data *data, int fd_inf, int fd_outf)
{
	data->id = ft_fork();
	if (data->id == 0)
	{
		sig_child();
		check_infile(token, data, fd_inf);
		check_outfile(token, data, fd_outf);
		if (token->next && token->next->type == CMD)
			close(data->fd[READ]);
		if (execve(token->path, token->args, data->envi) == -1)
		{
			free_data(data);
			exit(1);
		}
		free_data(data);
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

void	set_nodes(t_token **new_head, t_token **new_node, t_token **current_new)
{
	if ((*new_head) == NULL)
	{
		(*new_head) = (*new_node);
		(*current_new) = (*new_node);
	}
	else
	{
		(*current_new)->next = (*new_node);
		(*new_node)->prev = (*current_new);
		(*current_new) = (*new_node);
	}
}

t_token	*copy_without_pipe(t_token *token)
{
	t_token	*new_head;
	t_token	*struct_cpy;
	t_token	*current_new;
	t_token	*new_node;

	new_head = NULL;
	struct_cpy = token;
	current_new = NULL;
	while (struct_cpy != NULL)
	{
		if (struct_cpy->type != PIPE)
		{
			new_node = (t_token *)malloc(sizeof(t_token));
			if (new_node == NULL)
				return (NULL);
			new_node->args = struct_cpy->args;
			new_node->type = struct_cpy->type;
			new_node->redir = struct_cpy->redir;
			new_node->path = struct_cpy->path;
			new_node->next = NULL;
			set_nodes(&new_head, &new_node, &current_new);
		}
		struct_cpy = struct_cpy->next;
	}
	return (new_head);
}

void	wait_child_process(t_token *token, t_data *data)
{
	int	status;

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
}

void	exec_loop(t_data *data, t_token *tmp, int *fd_prueba, int n_pipes)
{
	int		i;

	i = -1;
	while (tmp && ++i <= n_pipes)
	{
		if (ft_is_builtin(tmp) == 0)
			*fd_prueba = prueba_builtin(tmp, data);
		else if (i == n_pipes)
			ft_executer(tmp, data, *fd_prueba, STDOUT_FILENO);
		else
			*fd_prueba = ft_exec_pipes(tmp, data, *fd_prueba);
		free(tmp->path);
		tmp = tmp->next;
	}
}

void	ft_exec(t_token *token, t_data *data)
{
	t_token	*tmp;
	t_token	*first;
	int		fd_prueba;
	int		n_pipes;

	tmp = copy_without_pipe(token);
	first = tmp;
	n_pipes = get_pipes(token);
	ft_check_cmd_path(tmp, data);
	ft_check_redir(tmp, data);
	if (data->del != NULL)
		ft_here_doc(tmp, data);
	tmp = first;
	fd_prueba = STDIN_FILENO;
	exec_loop(data, tmp, &fd_prueba, n_pipes);
	data->del = NULL;
	data->outfile = NULL;
	data->infile = NULL;
	free_tokens_no_mtx(first);
	if (fd_prueba != STDIN_FILENO)
		close(fd_prueba);
	wait_child_process(token, data);
}
