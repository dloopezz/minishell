/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:24:42 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/20 15:21:54 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"

//TODO investigar combinaciones posibles de donde puede estar file
t_token	*swap_nodes(t_token *cur)
{
	t_token	*aux1;
	t_token	*aux2;

	aux1 = cur;
	aux2 = cur->next;

	if (cur == NULL || cur->next == NULL)
		return (cur);
	// adjust prev pointer of aux1
	if (aux1->prev != NULL)
		aux1->prev->next = aux2;
	// adjust next pointer of aux2
	if (aux2->next != NULL)
		aux2->next->prev = aux1;

	cur->next = aux2->next;
	aux2->prev = aux1->prev;
	aux1->prev = aux2;
	aux2->next = aux1;

	return (aux2); // return new head after swap (aux2 is now the head)
}

void	check_type(t_token *aux)
{
	if (aux->type == LT)
		printf("entra LT\n");
	if (aux->type == LLT)
		printf("entra LLT\n");
	if (aux->type == GT)
	{
		printf("entra GT\n");
		// aux = handle_outfile(aux);
	}
	if (aux->type == GGT)
		printf("entra GGT\n");
}

void	handle_redirs(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	// while (aux)
	// {
	// 	if (is_redir(aux->type))
	// 		check_type(aux);
	// 	aux = aux->next;	
	// }
	// aux = tokens;
	// swap_nodes(aux);
	// read_list(aux);
}
