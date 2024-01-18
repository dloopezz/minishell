/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:03:59 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/18 17:03:18 by crtorres         ###   ########.fr       */
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
	data->line = NULL;
	// free_tokens(aux);
	data->tokens = NULL;
}
