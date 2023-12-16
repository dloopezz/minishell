/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:36:08 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/16 17:37:01 by dlopez-s         ###   ########.fr       */
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

void	get_next_pipe(t_data *data, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens && tokens->type == PIPE)
		tokens = tokens->next;
	data->token_aux = tokens;
}

void	do_cmd(t_token *tokens, t_data *data, int fdin, int fdout)
{
	int	redir_flag;

	redir_flag = 0;
	while (data->token_aux && data->token_aux->type != PIPE)
	{
		if (is_redir(data->token_aux->type))
		{
			redir_flag = 1;
			break ;
		}
		data->token_aux = data->token_aux->next;
	}
	if (redir_flag == 1)
		handle_redir(tokens, data, fdin, fdout);
	else
		process_cmd(tokens, data, fdin, fdout);
}

void	ft_execute(t_token *tokens, t_data *data)
{
	int		n_pipes;
	int		fds[2];
	int		fdin;
	int		i;
	t_token	*head;

	n_pipes = get_pipes(tokens);
	head = tokens;
	data->token_aux = tokens;
	fdin = STDIN_FILENO;
	i = 0;
	while (data->token_aux && i <= n_pipes)
	{
		tokens = data->token_aux;
		if (pipe(fds) == -1)
			exit(1);
		if (i == n_pipes)
			do_cmd(tokens, data, fdin, STDOUT_FILENO);
		else
			do_cmd(tokens, data, fdin, fds[1]);
		close(fds[1]);
		fdin = fds[0];
		get_next_pipe(data, tokens);
		i++;
	}
	tokens = head;
}
