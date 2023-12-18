/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:03:59 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/18 16:30:56 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		// printf("MTX[i]: %s-(%p)\n", mtx[i], mtx[i]);
		mtx[i] = NULL;
		free(mtx[i]);
		// printf("MTX[i]: %s-(%p)\n", mtx[i], mtx[i]);
		i++;
	}
	mtx[i] = NULL;
	free(mtx);
}

void	free_tokens(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	while (tokens)
	{
		aux = tokens->next;
		free_mtx(tokens->args);
		// tokens = NULL;
		free(tokens);
		tokens = aux;
	}
}

void	free_data(t_data *data)
{
	t_token	*aux;

	aux = data->tokens;
	free(data->line);
	free_tokens(aux);
	data->tokens = NULL;
}
