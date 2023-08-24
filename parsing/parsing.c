/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/08/24 17:20:51 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*add_token(t_token *cmd_lst, char *cmd)
{
	t_token	*new;
	t_token	*aux;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	new->data = cmd;
	// new->type = token_type;
	new->next = NULL;
	if (!cmd_lst)
		cmd_lst = new;
	else
	{
		aux = cmd_lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	return (cmd_lst);
}

int	select_type(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (LLT);
		else
			return (LT);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (GGT);
		else
			return (GT);
	}
	else
		return (CMD);
}

char	**divide_cmds(char *line, int token_type, int i)
{
	
}

int	ft_parsing(char *line)
{
	int		i;
	int		token_type;
	char	**cmds;
	// t_token	*cmd_lst;

	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);

	// cmd_lst = ft_calloc(1, sizeof(t_token));
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ') //poner tb \t y eso 
			i++;

		token_type = select_type(line, i);
		cmds = divide_cmds(line, token_type, i);	
 	}
	return (0);
}
