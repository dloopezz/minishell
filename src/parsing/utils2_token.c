/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:45:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/16 16:49:19 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token	*re_type(t_token *token, int type_find, int new_type, int prev_type)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (cur->prev && cur->type == type_find && cur->prev->type == prev_type)
			cur->type = new_type;
		cur = cur->next;
	}
	return (token);
}

t_token	*re_type_all(t_token *tokens)
{
	tokens = re_type(tokens, CMD, DELM, LLT);
	tokens = re_type(tokens, CMD, INFILE, LT);
	tokens = re_type(tokens, CMD, OUTFILE, GT);
	tokens = re_type(tokens, CMD, OUTFILE, GGT);
	return (tokens);
}

void	set_redir(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	while (aux)
	{
		if (aux->type == LT)
			aux->redir = "2";
		else if (aux->type == LLT)
			aux->redir = "3";
		else if (aux->type == GT)
			aux->redir = "4";
		else if (aux->type == GGT)
			aux->redir = "5";
		aux = aux->next;
	}
}
