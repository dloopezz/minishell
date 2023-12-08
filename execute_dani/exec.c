/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:36:08 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/08 17:31:15 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	get_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens->type == PIPE)  //lo mismo puedo meter este if en el while y tirando
		tokens = tokens->next;
}

void	handle_redir(t_token *tokens, t_data *data, int fdin, int fdout)
{
	t_token	*aux;

	aux = tokens;
	//check valid redir function
	// if (tokens->type == LT)
	// 	//handle_infile()
	// else if (tokens->type == LLT)
	// 	//handle_heredoc()
	// else if (tokens->type == GT)
	// 	//handle_outile()
	// else if (tokens->type == GGT)
	// 	//handle_outfile()
	if (aux->next && is_redir(aux->next->type))
	{
		tokens = aux->next; // ??
		handle_redir(tokens, data, fdin, fdout);
	}
	else
		process_cmd(tokens, data, fdin, fdout);
	
}

void	do_cmd(t_token *tokens, t_data *data, int fdin, int fdout)
{
	int redir_flag;

	redir_flag = 0;
	while(tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
		{
			redir_flag = 1;
			break ;
		}
		tokens = tokens->next;
	}
	if (redir_flag == 1)
		handle_redir(tokens, data, fdin, fdout);
	else
		process_cmd(tokens, data, fdin, fdout); //cambiar nombre (muy parecido)	
}

void	ft_execute(t_token *tokens, t_data *data)
{
	t_token	*aux;
	int n_pipes;
	int	fds[2];
	int fdin;
	int	i;

	i = 0;
	aux = tokens;
	n_pipes = get_pipes(aux);
	fdin = STDIN_FILENO;
	while (aux && i <= n_pipes)
	{
		if (pipe(fds) == -1)
			exit(1); //perror
		if (i == n_pipes)
			do_cmd(aux, data, fdin, STDOUT_FILENO);
		else
			do_cmd(aux, data, fdin, fds[1]);
		close(fds[1]);
		fdin = fds[0];
		get_next_pipe(tokens);
		i++;
	}		
}