/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/08 16:41:38 by crtorres         ###   ########.fr       */
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
	
	if (strlen(file) > sizeof(file))
        return (-1);
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

void	ft_check_redir(t_token *token)
{
	int	file;
	while (token)
	{
		if (is_redir(token->type))
		{
			if (token->type == GT)
				file = open_file(*token->next->args, 1);
			else if (token->type == GGT)
				file = open_file(*token->next->args, 2);
			close(file);
		}
		token = token->next;
	}
}

void 	ft_exec(t_token *token, t_data *data)
{
	int	status;
	data->id = 0;
	t_token *tmp = copyWithoutPipe(token);
	int	fd_prueba;
	ft_check_cmd_path(tmp, data);
	ft_check_redir(tmp);
	ft_here_doc(tmp, data);
	fd_prueba = STDIN_FILENO;
	while (tmp)
	{
		if (ft_is_builtin(tmp) == 0)
			fd_prueba = ft_builtin(tmp, data);
		else if (!tmp->next || tmp->next->type != CMD)
			ft_executer(tmp, data, fd_prueba, STDOUT_FILENO);
		else
			fd_prueba = ft_exec_pipes(tmp, data, fd_prueba);
		tmp = tmp->next;
	}
	//dup2(STDOUT_FILENO, STDIN_FILENO);
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

/**
 * two types of struct
 * 
 * ls -la | cat > out >> infile -e
 * 
 * 
 * struct command
 * type CMD 
 * args[0] cat
 * char **items -e 
 * char **redir > >> 
 * char **io out infile
 * 
 * struct pipe
 * type PIPE
 * args NULL
 * 
 * ls -la | cat > out >> infile > test | wc
 * ar 	    ar  re ar re  ar.  re  ar   ar
 * 
 * char *delimitors = {<<, <, >>, >, |};
 * size_t i = 0;
 * while (tokens != NULL)
 * {
 * 		while (i < 5)
 * 		{
	* 		if (tokens == delimitors[i])
	* 			type = delim;
			i++;
 * 		}
 * 		
 * }
 * 
 * 
 *  typedef struc token

 * 		char **args	
 * 		int type			CMD, DELI, PIPE
 * 
 * 
 * ls > out 
 * check infile 
 * 		ls
 * 		>
 * 		out
 * 			check type 
 * 				if type == CMD
 * 					return / token.next
 * 				if type == 
*/








///      ls					> 				out
///	 fd[0]  fd[1].      fd[0]. fd[1].     fd[0] fd[1]
//			fd[1(ls)]-fd[0(>)].    