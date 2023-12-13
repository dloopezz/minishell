/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:42:06 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/13 11:53:30 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_case(t_token *file, t_token *cmd)
{
	int 	i;
	int 	j;
	char	**new_args;
																//-1 quita file
	new_args = (char **)ft_calloc(sizeof(char *), (ft_matrix_len(file->args) - 1) + ft_matrix_len(cmd->args) + 1);
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
	//old_args liberado pero no estoy seguro del todo, si hay leaks comprobar
	free_mtx(cmd->args);
	cmd->args = new_args;
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
	if (aux && aux->type == CMD && aux->next->next && (aux->next->next->type == OUTFILE || aux->next->next->type == INFILE || aux->next->next->type == DELM))
		return (1);
	else if (aux && is_redir(aux->type) && aux->next && (aux->next->type == INFILE || aux->next->type == OUTFILE || aux->next->type == DELM) && aux->next->args[1]) //que file tenga args
		return (2);
	else
		return (0);
}

void	reorder_tokens(t_token **tokens)
{
	t_token *cmd;
	t_token *aux;
	
	aux = *tokens;
	while (aux->next)
	{
		if (choose_case(aux) == 1)
		{
			cmd = aux;
			first_case(aux->next->next, cmd);
		}
		if (choose_case(aux) == 2)
			*tokens = second_case(*tokens, aux->next);
		aux = aux->next;
	}
}
