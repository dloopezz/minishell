/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:36:52 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/28 11:41:47 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	count_heredocs(t_token *token, t_data *data)
{
	int		i;
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
	int		i;
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

void	put_content_hd(int index, t_heredoc *hd, t_data *data)
{
	char	*line;
	char	*line_aux;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, hd[index].delim, ft_strlen(line) + 1) == 0)
			break ;
		line_aux = ft_expand(data, line);
		line = ft_strtrim(line_aux, "\"");
		free(line_aux);
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

void	ft_here_doc(t_token *token, t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;
	t_token	*tmp;

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
			put_content_hd(i, data->heredc, data);
		while (++i < data->n_her_doc)
			free_struct(data->heredc, i);
		exit(1);
	}
	else if (pid > 0)
	{
		i = -1;
		while (++i < data->n_her_doc)
			close(data->heredc[i].fd[WRITE]);
	}
	waitpid(pid, &status, 0);
}
