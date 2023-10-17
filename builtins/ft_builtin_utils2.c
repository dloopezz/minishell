/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:56:28 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/16 12:27:44 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listsize(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

bool	is_absolute_path(const char *path)
{
	if (!path || path[0] == '\0')
		return (false);
	return (true);
}

int	ft_matrix_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_clear_cd(char *old_path, char *current_path, int i)
{
	if (i == 1)
		free (old_path);
	else if (i == 2)
	{
		free (old_path);
		free (current_path);
	}
}
