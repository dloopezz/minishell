/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:00:26 by lopezz            #+#    #+#             */
/*   Updated: 2024/01/19 14:57:17 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_redir(int type)
{
	if (type == LT || type == LLT || type == GT || type == GGT)
		return (true);
	return (false);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

size_t	count_words(const char	*str, char c)
{
	size_t	countw;
	size_t	i;

	countw = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != c && str[i] != 0)
		{
			countw++;
			while (str[i] != c && str[i] != 0)
				i++;
		}
		else if (str[i] != 0)
			i++;
	}
	return (countw);
}
