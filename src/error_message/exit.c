/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:03:59 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/31 11:59:53 by dlopez-s         ###   ########.fr       */
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
	if (!tokens)
		return ;
	while (tokens && tokens->next)
	{
		if (tokens->next)
			aux = tokens->next;
		free_mtx(tokens->args);
		free(tokens);
		tokens = aux;
	}
	// if (tokens)
	// {
		free_mtx(tokens->args);
		free(tokens);
	// }
}

void	free_tokens_no_mtx(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	if (!tokens)
		return ;
	while (tokens && tokens->next)
	{
		if (tokens->next)
			aux = tokens->next;
		free(tokens);
		tokens = aux;
	}
	free(tokens);
}

void	free_data(t_data *data)
{
	t_token	*aux;

	aux = data->tokens;
	free(data->line);
	data->line = NULL;
}
