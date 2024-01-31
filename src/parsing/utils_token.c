/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:38:34 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/31 12:09:24 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// //!quitar pa entregar
void	read_list(t_token *cmd_lst)
{
	t_token	*aux_lst;
	int		i;

	aux_lst = cmd_lst;
	while (aux_lst)
	{
		i = 0;
		printf("\n\033[33mNEW ARG: \033[0m\n");
		while (aux_lst->args[i])
		{
			printf("ARG[i]: |%s|\n", aux_lst->args[i]);
			i++;
		}
		printf("TYPE: %d\n", aux_lst->type);
		aux_lst = aux_lst->next;
	}
	printf("\n");
}

//conts: 
// 0 - i
// 1 - j
// 2 - n
char	**split_cmd(t_token *tokens, char *cmd)
{
	int	conts[3];

	conts[0] = 0;
	conts[1] = 0;
	conts[2] = 0;
	tokens->args = ft_calloc(sizeof(char *), count_words(cmd, ' ') + 3);
	while (cmd[conts[0]])
	{
		tokens->args[conts[2]] = ft_calloc(1, ft_strlen(cmd) + 1);
		if (!tokens->args[conts[2]])
			exit(EXIT_FAILURE);
		if (cmd[conts[0]] == '\0')
			break ;
		if (cmd[conts[0]] == DQUOTES || cmd[conts[0]] == SQUOTES)
			conts[0] = select_mode(tokens, cmd, conts, QUOTED);
		else
			conts[0] = select_mode(tokens, cmd, conts, UNQUOTED);
		conts[2]++;
	}
	tokens->args[conts[2]] = NULL;
	return (tokens->args);
}

t_token	*add_token_data(t_token *token, int type, int quotes)
{
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	token->quotes = quotes;
	return (token);
}

t_token	*add_token(t_token *cmd_lst, char *cmd, int type, int quotes)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	if (quotes == UNCLOSED)
		new->args = NULL;
	else
	{
		new->args = split_cmd(new, cmd);		
		if (ft_strcmp(*new->args, "") == 0)
		{
			free_tokens(cmd_lst);
			free_tokens(new);
			return (err_syntax("Syntax error near unexpected token ", 1), NULL);
		}
	}
	new = add_token_data(new, type, quotes);
	set_redir(new);
	if (!cmd_lst)
		cmd_lst = new;
	else
	{
		aux = cmd_lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
		new->prev = aux;
	}
	if (quotes == UNCLOSED && !new->prev)
		free(new);
	return (cmd_lst);
}

t_token	*add_tokenfront(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	new->args = split_cmd(new, cmd);
	new->type = type;
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
