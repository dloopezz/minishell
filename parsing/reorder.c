/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:42:06 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/12 19:17:53 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_case(t_token *file, t_token *head)
{
	int i = 1;
	while (file->args[i])
	{
		head->args[i] = file->args[i];
		file->args[i] = NULL;
		i++;
	}
}

t_token	*second_case(t_token *tokens, t_token *file)
{
	int		i = 1;
	char	*cmd = "";
	
	while (file->args[i])
	{
		cmd = ft_strjointhree(cmd, " ", file->args[i]);
		file->args[i] = NULL;
		i++;
	}
	tokens = add_tokenfront(tokens, cmd, CMD);
	return (tokens);
}

int	choose_case(t_token *aux)
{
	if (aux->type == CMD && (aux->next->next->type == OUTFILE || aux->next->next->type == INFILE))
		return (1);
	if ((aux->type == LT || aux->type == GT || aux->type == GGT) && (aux->next->type == INFILE || aux->next->type == OUTFILE) && aux->next->args[1]) //que file tenga args
		return (2);
	return (0);
}

void	reorder_tokens(t_token **tokens)
{
	t_token *cmd;
	t_token *aux;
	
	aux = *tokens;
	while (aux->next)
	{
		//checkear que existan tb para que no pete
		if (choose_case(aux) == 1)
		{
			cmd = aux;
			first_case(aux->next->next, cmd);
		}
		if (choose_case(aux) == 2)
			*tokens = second_case(*tokens, aux->next);
		// if (choose_case(aux) == 3)
			// heredoc
		aux = aux->next;
	}
	// read_list(tokens);	
}
