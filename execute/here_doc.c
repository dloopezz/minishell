/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:39:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/30 12:51:20 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ft_strncmp(line, hd[index].delim, ft_strlen(line) + 1) == 0)
			break;
		ft_putendl_fd(line, hd->fd[1]);
		free (line);
		line = readline("> ");
	}
	free (line);
	close(hd[index].fd[1]);
	close(hd[index].fd[0]);
}
void	free_struct(t_heredoc *hd, int nb_hd)
{
	int	i;

	i = -1;
	while (++i < nb_hd)
		free(&hd[i]);	
	hd = NULL;
}
void	ft_here_doc(t_token *token, t_data *data)
{
	int i;
	pid_t pid;
	int status;
	//char *doc_exit;
	//t_heredoc *h_doc;

	count_heredocs(token, data);
	data->heredc = ft_calloc(sizeof(t_heredoc), data->n_her_doc);
	hd_delims(token, data->heredc);
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
		data->heredc = NULL;
		exit(1);
	}
	else if(pid > 0)
	{
		i = -1;
		while (++i < data->n_her_doc)
			close(data->heredc[i].fd[1]);
	}
	waitpid(pid, &status, 0);
}
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