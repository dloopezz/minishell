/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:03:59 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/18 19:09:20 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		free(mtx[i]);
		mtx[i] = NULL;
		i++;
	}
	free(mtx);
	mtx[i] = NULL;
} */
void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		free(mtx[i]);
		mtx[i] = NULL;
		i++;
	}
	free(mtx);
	mtx = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*aux;
	
	aux = tokens;
	while (tokens)
	{
		aux = tokens->next;
		free_mtx(tokens->args);
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
