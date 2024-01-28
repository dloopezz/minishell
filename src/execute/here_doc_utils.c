/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:34:44 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/28 12:35:30 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	count_heredocs(t_token *token, t_data *data)
{
	int		i;
	t_token	*aux;

	i = 0;
	aux = token;
	while (aux && aux->next)
	{
		if (aux->type == LLT)
			i++;
		aux = aux->next;
	}
	data->n_her_doc = i;
}

void	free_struct(t_heredoc *hd, int nb_hd)
{
	int	i;

	i = -1;
	while (++i < nb_hd)
		free(&hd[i]);
	hd = NULL;
}
