/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:42:06 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/27 14:57:26 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	choose_case(t_token *aux)
{
	if (aux && aux->type == CMD && aux->next->next
		&& (aux->next->next->type == OUTFILE || aux->next->next->type == INFILE
			|| aux->next->next->type == DELM) && aux->next->next->args[1])
		return (1);
	else if (aux && is_redir(aux->type) && aux->next
		&& (aux->next->type == INFILE || aux->next->type == OUTFILE
			|| aux->next->type == DELM) && aux->next->args[1])
		return (2);
	else
		return (0);
}

void	prepare_case(t_token **aux, t_token **cmd, int type)
{
	t_token	*aux2;

	aux2 = *aux;
	if (type == 1)
	{
		while (aux2->next && aux2->next->next && !aux2->next->next->args[1])
			aux2 = aux2->next->next;
		*cmd = *aux;
		if (aux2->next && aux2->next->next && aux2->next->next->args[1])
			*aux = aux2;
	}
	else if (type == 2)
	{
		aux2 = *aux;
		while (aux2 && aux2->next && !aux2->next->args[1])
			aux2 = aux2->next;
		if (aux2 && aux2->next && aux2->next->args[1])
			*aux = aux2;
	}
}

void	reorder_tokens(t_token **tokens)
{
	t_token	*cmd;
	t_token	*aux;
	int		is_first;

	is_first = 0;
	aux = *tokens;
	cmd = NULL;
	while (aux && aux->next)
	{
		if (choose_case(aux) == 1)
		{
			prepare_case(&aux, &cmd, 1);
			first_case(aux->next->next, cmd);
		}
		if (choose_case(aux) == 2)
		{
			prepare_case(&aux, &cmd, 2);
			second_case(tokens, aux->next, is_first);
			is_first = 1;
		}
		aux = aux->next;
	}
}
