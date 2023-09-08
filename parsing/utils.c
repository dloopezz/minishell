/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:00:26 by lopezz            #+#    #+#             */
/*   Updated: 2023/09/08 15:27:19 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//!quitar pa entregar
void read_list(t_token *cmd_lst)
{
	t_token	*aux_lst;

	aux_lst = cmd_lst;
	while (aux_lst)
	{
		printf("\nLST_DATA: %s\n", aux_lst->data);
		// //para detectar espacios
		// int k = 0;
		// while (aux_lst->data[k])
		// {
		// 	if (aux_lst->data[k] == 32)
		// 	{
		// 		printf("\033[31mCHAR: SPACE \u26A0\033[0m\n");
		// 		k++;
		// 	}
		// 	else
		// 		printf("CHAR: %c\n", aux_lst->data[k++]);
		// }
		printf("LST_TYPE: %d\n", aux_lst->type);
		aux_lst = aux_lst->next;	
	}
}

t_token	*add_token(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	new->data = cmd;
	new->type = type;
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

bool is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
