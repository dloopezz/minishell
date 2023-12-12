/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:42:06 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/12 18:26:22 by dlopez-s         ###   ########.fr       */
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

t_token	*add_tokenfront(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	new->args = split_cmd(new, cmd);
	new->type = type;
	new->path = NULL;
	set_redir(new);
	if (!cmd_lst)
		cmd_lst = new;
	else
	{
		new->next = cmd_lst;
		new->prev = NULL;
		cmd_lst = new;
	}
	return (cmd_lst);
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

void	reorder_tokens(t_token **tokens)
{
	t_token *cmd;
	t_token *aux;
	
	aux = *tokens;
	while (aux->next)
	{
		//checkear que existan tb para que no pete
		if (aux && aux->type == CMD && (aux->next->next->type == OUTFILE || aux->next->next->type == INFILE))
		{
			cmd = aux;
			first_case(aux->next->next, cmd);
		}
		if (aux && (aux->type == LT || aux->type == GT) && (aux->next->type == INFILE || aux->next->type == OUTFILE) && aux->next->args[1]) //que file tenga args
		{	
			*tokens = second_case(*tokens, aux->next);
		}
		aux = aux->next;
	}
	// read_list(tokens);
	
}
