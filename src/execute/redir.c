/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:35:25 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/19 16:59:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	handle_infile(t_data *data, int fdin)
{
	int	file_fd;

	data->token_aux = data->token_aux->next;
	file_fd = open_file(data->token_aux->args[0], 0);
	if (fdin != STDIN_FILENO)
		close(fdin);
	return (file_fd);
}

int	handle_outfile(t_data *data, int fdout, int type)
{
	int	file_fd;

	data->token_aux = data->token_aux->next;
	if (type == GT)
		file_fd = open_file(data->token_aux->args[0], 1);
	if (type == GGT)
		file_fd = open_file(data->token_aux->args[0], 2);
	if (file_fd == -1)
		return (-1);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (file_fd);
}

int	handle_heredoc(t_data *data, int fdin)
{
	char	*del;
	char	*line;
	int		tmpfile;

	data->token_aux = data->token_aux->next;
	del = data->token_aux->args[0];
	printf("del es [%s]\n", del);
	tmpfile = open_file(".tmp", 1);
	line = readline("> ");
	while (ft_strcmp(line, del) != 0)
	{
		line = ft_expand(data, line);
		line = ft_strtrim(line, "\"");
		ft_putendl_fd(line, tmpfile);
		free(line);
		line = readline("> ");
	}
	close(tmpfile);
	tmpfile = open(".tmp", O_RDONLY);
	free(del);
	free(line);
	if (fdin != STDIN_FILENO)
		close(fdin);
	fdin = tmpfile;
	unlink(".tmp");
	return (fdin);
}

void	handle_redir(t_token *tokens, t_data *data, int fdin, int fdout)
{
	t_token	*aux;

	aux = data->token_aux;
	if (data->token_aux->type == GT)
		fdout = handle_outfile(data, fdout, GT);
	else if (data->token_aux->type == GGT)
		fdout = handle_outfile(data, fdout, GGT);
	if (fdout == -1)
		return ;
	else if (data->token_aux->type == LT)
		fdin = handle_infile(data, fdin);
	else if (data->token_aux->type == LLT)
		fdin = handle_heredoc(data, fdin);
	if (fdin == -1)
		return ;
	aux = aux->next;
	if (aux->next && is_redir(aux->next->type))
	{
		data->token_aux = aux->next;
		handle_redir(tokens, data, fdin, fdout);
	}
	else
		process_cmd(tokens, data, fdin, fdout);
}
