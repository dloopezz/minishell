/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:36:52 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/26 11:56:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void count_heredocs(t_token *token, t_data *data)
{
	int i;
	t_token	*aux;

	i = 0;
	aux = token;
	while (aux && aux->next)
	{
		if (aux->type == LLT)
			i++;
		aux = aux->next;
	}
	data->n_her_doc = i;
}
void	hd_delims(t_token *token, t_heredoc *hd)
{
	int	i;
	t_token	*aux;

	i = 0;
	aux = token;
	while (aux && aux->next)
	{
		if (aux->type == LLT)
		{
			aux = aux->next;
			hd[i].delim = *aux->args;
			printf("hd[i].delim es %s\n", hd[i].delim);
			pipe(hd[i++].fd);
		}
		aux = aux->next;
	}
}
void	put_content_hd(int index, t_heredoc *hd)
{
	char *line;

	line = readline("> ");
	while (line)
	{
		//hd[index].fd[0] = open_file(data->file_hd, 1);
		if (ft_strncmp(line, hd[index].delim, ft_strlen(line) + 1) == 0)
			break;
		ft_putendl_fd(line, hd[index].fd[WRITE]);
		free (line);
		line = readline("> ");
	}
	free (line);
	close(hd[index].fd[WRITE]);
	close(hd[index].fd[READ]);
}

void	free_struct(t_heredoc *hd, int nb_hd)
{
	int	i;

	i = -1;
	while (++i < nb_hd)
		free(&hd[i]);	
	hd = NULL;
}

/* void	ft_wait_for_heredoc(t_data *data, pid_t	pid)
{
	int	fd;
	int	status;

	sig_ignore();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			//g_minishell.exit_status = 1;
			//ps->ctl_c_hd = 1;
			if (access(data->file_hd, F_OK) != -1)
			{
				fd = open_file(data->file_hd, 1);
				close(fd);
			}
		}
	}
	sig_parent();
} */

void	ft_here_doc(t_token *token, t_data *data)
{
	int i;
	pid_t pid;
	int status;
	t_token *tmp;
	//char *doc_exit;
	//t_heredoc *h_doc;

	tmp = token;
	count_heredocs(tmp, data);
	data->heredc = ft_calloc(sizeof(t_heredoc), data->n_her_doc);
	hd_delims(tmp, data->heredc);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		sig_heredoc();
		i = -1;
		while (++i < data->n_her_doc)
			put_content_hd(i, data->heredc);
		while (++i < data->n_her_doc)
			free_struct(data->heredc, i);
		//data->heredc = NULL;
		//close(data->heredc->fd[0]);
		exit(1);
	}
	//ft_wait_for_heredoc(data, pid);
	else if(pid > 0)
	{
		i = -1;
		while (++i < data->n_her_doc)
		{
			//printf("ENTRA EN EL WHILEEE\n");
			//data->heredc[i].fd[0] = open_file(data->file_hd, 1);
			close(data->heredc[i].fd[WRITE]);
		}
			//close(data->heredc[i].fd[WRITE]);
	}
	waitpid(pid, &status, 0);
}

/* int	heredoc_loop(char *line, int tmpfile, t_data **data)
{
	//char	*del;
	char	*line_aux;

	printf("token en hd_loop es %s\n", *(*data)->token_aux->args);
	//(*data)->token_aux = (*data)->token_aux->next->next;
	//del = (*data)->token_aux->args[0];
	printf("del es %s\n", (*data)->del[0]);
	line = readline("> ");
	while (ft_strcmp(line, (*data)->del[0]) != 0)
	{
		line_aux = ft_expand(*data, line);
		line = ft_strtrim(line_aux, "\"");
		free(line_aux);
		ft_putendl_fd(line, tmpfile);
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

int	handle_heredoc(t_data *data, int fdin)
{
	char	*line;
	int		tmpfile;

	printf("entra en hd\n");
	line = NULL;
	sig_ignore();
	tmpfile = open_file(".tmp", 1);
	sig_heredoc();
	if (heredoc_loop(line, tmpfile, &data))
		return (exec_exit_error(6, ""), -1);
	close(tmpfile);
	tmpfile = open(".tmp", O_RDONLY);
	if (fdin != STDIN_FILENO)
		close(fdin);
	fdin = tmpfile;
	unlink(".tmp");
	return (fdin);
} */

	/* printf("es %s\n", *token->next->next->next->next->next->args);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			if (access(*token->next->args, F_OK) != -1)
			{
				data->heredc->fd[0] = open(*token->next->args, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				close(data->heredc->fd[1]);
			}
		}
	} */


/* void	put_here_doc(t_token *token, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	line = readline("> ");
	while (line)
	{
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