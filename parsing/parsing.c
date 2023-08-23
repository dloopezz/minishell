/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/08/23 19:01:41 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*add_node(t_node *cmd_lst, char *cmd)
{
	t_node	*new;
	t_node	*aux;

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	new->data = cmd;
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

int	ft_parsing(char *line)
{
	t_node	*cmd_lst;
	char	*cmd = NULL;
	int		i;
	int		j;

	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);

	cmd_lst = ft_calloc(1, sizeof(t_node));
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			//algo
			printf("llega\n");		                                                       
		}
		else
		{
			j = 0;
			add_node(cmd_lst, cmd);
			// free(cmd);
		}
	}
	
	return (0);
}
