/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:42:06 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/18 14:53:13 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	first_case(t_token *file, t_token *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = (char **)ft_calloc(sizeof(char *),
			(ft_matrix_len(file->args) - 1) + ft_matrix_len(cmd->args) + 1);
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	j = 0;
	while (file->args[++j])
	{
		new_args[i++] = file->args[j];
		file->args[j] = NULL;
		free(file->args[j]);
	}
	free_mtx(cmd->args);
	cmd->args = new_args;
}

t_token	*second_case(t_token *tokens, t_token *file, int is_first)
{
	int		i;
	char	*cmd;
	char	*first_cmd;
	char	**cmd_tab;

	i = 1;
	cmd = "";
	first_cmd = "";
	while (file->args[i])
	{
		cmd = ft_strjointhree(cmd, " ", file->args[i]);
		file->args[i] = NULL;
		i++;
	}
	if (is_first == 0)
		tokens = add_tokenfront(tokens, cmd, CMD);
	else
	{
		first_cmd = tokens->args[0];
		cmd_tab = ft_split(cmd, ' ');
		i = 0;
		free_mtx(tokens->args);
		tokens->args = (char **)ft_calloc(sizeof(char *),
				ft_matrix_len(file->args) + ft_matrix_len(cmd_tab) + 1);
		tokens->args[0] = first_cmd;
		while (cmd_tab[i])
			tokens->args[ft_matrix_len(tokens->args)] = cmd_tab[i++];
	}
	return (tokens);
}

int	choose_case(t_token *aux)
{
	if (aux && aux->type == CMD && aux->next->next
		&& (aux->next->next->type == OUTFILE || aux->next->next->type == INFILE
			|| aux->next->next->type == DELM))
		return (1);
	else if (aux && is_redir(aux->type) && aux->next
		&& (aux->next->type == INFILE || aux->next->type == OUTFILE
			|| aux->next->type == DELM) && aux->next->args[1])
		return (2);
	else
		return (0);
}

void	reorder_tokens(t_token **tokens)
{
	t_token	*cmd;
	t_token	*aux;
	t_token	*aux2;
	int		is_first;

	is_first = 0;
	aux = *tokens;
	aux2 = *tokens;
	while (aux && aux->next)
	{
		if (choose_case(aux) == 1)
		{
			aux2 = aux;
			while (aux2->next && aux2->next->next && !aux2->next->next->args[1])
				aux2 = aux2->next->next;
			cmd = aux;
			if (aux2->next && aux2->next->next && aux2->next->next->args[1])
				aux = aux2;
			first_case(aux->next->next, cmd);
		}
		if (choose_case(aux) == 2)
		{
			aux2 = aux;
			while (aux2 && aux2->next && !aux2->next->args[1])
				aux2 = aux2->next;
			if (aux2 && aux2->next && aux2->next->args[1])
				aux = aux2;
			*tokens = second_case(*tokens, aux->next, is_first);
			is_first = 1;
		}
		aux = aux->next;
	}
}
