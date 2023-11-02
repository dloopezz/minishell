/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:24:42 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/02 11:50:18 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO investigar combinaciones posibles de donde puede estar file
// void	handle_infile(t_token *aux)
// {
// 	//buscar file en aux->next
// }

void	check_type(t_token *aux)
{
	// oldprev->args[0] = NULL; //para unused var
	if (aux->type == LT)
	{
		printf("entra LT\n");
		printf("PREV_ARG: |%s|\n", aux->prev->args[0]);
		// handle_infile(aux);
	}
	if (aux->type == LLT)
		printf("entra LLT\n");
	if (aux->type == GT)
		printf("entra GT\n");
	if (aux->type == GGT)
		printf("entra GGT\n");
}

void	handle_redirs(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	while (aux)
	{
		if (is_redir(aux->type))
			check_type(aux);
		aux = aux->next;	
	}
}
