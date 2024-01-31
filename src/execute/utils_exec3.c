/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:54:27 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/31 16:51:21 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_nodes(t_token **new_head, t_token **new_node, t_token **current_new)
{
	if ((*new_head) == NULL)
	{
		(*new_head) = (*new_node);
		(*current_new) = (*new_node);
	}
	else
	{
		(*current_new)->next = (*new_node);
		(*new_node)->prev = (*current_new);
		(*current_new) = (*new_node);
	}
}

t_token	*copy_without_pipe(t_token *token)
{
	t_token	*new_head;
	t_token	*struct_cpy;
	t_token	*current_new;
	t_token	*new_node;

	new_head = NULL;
	struct_cpy = token;
	current_new = NULL;
	while (struct_cpy != NULL)
	{
		if (struct_cpy->type != PIPE)
		{
			new_node = (t_token *)malloc(sizeof(t_token));
			if (new_node == NULL)
				return (NULL);
			new_node->args = struct_cpy->args;
			new_node->type = struct_cpy->type;
			new_node->redir = struct_cpy->redir;
			new_node->path = struct_cpy->path;
			new_node->next = NULL;
			set_nodes(&new_head, &new_node, &current_new);
		}
		struct_cpy = struct_cpy->next;
	}
	return (new_head);
}

void	no_path(t_token **token, t_token **tmp)
{
	t_token	*head;
	t_token	*aux;

	head = (*token);
	aux = (*token);
	(*tmp) = head;
	while ((*tmp) && (*tmp)->next)
	{
		if ((*tmp)->next)
			aux = (*tmp)->next;
		if ((*tmp)->path)
			free((*tmp)->path);
		(*tmp) = aux;
	}
}

t_data	*reset_data(t_data *data)
{
	data->del = NULL;
	data->outfile = NULL;
	data->infile = NULL;
	return (data);
}
