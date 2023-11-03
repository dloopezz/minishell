/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/03 14:25:25 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_single_quotes(char *str, int *len)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] != SINGLE_QUOTES)
	{
		if (str[i] == '\0')
			break;
		i++;
		(*len)++;
	}
	(*len)++;
	return (i);
}

int	process_double_quotes(char *str, int *len, char **env)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] == '$')
		i += check_init_dollar(&str[i], len, NULL, env);
	if (str[i] == '\0')
		return (i);
	while (str[i] && str[i] != DOUBLE_QUOTES)
	{
		while (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], len, NULL, env);
		if (str[i] == '\0')
			return (i);
		(*len)++;
		i++;
	}
	(*len)++;
	return (i);
}

int doub_quotes(char *str, int *i, int *n_char, char *str_exp, t_data *env)
{
    str_exp[(*n_char)++] = str[(*i)++];
    while (str[*i] && str[*i] != DOUBLE_QUOTES)
    {
        if (str[*i] && str[*i] == '$' && str[*i + 1] != SINGLE_QUOTES && str[*i + 1] != DOUBLE_QUOTES)
            (*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
        if (str[*i] == '\0')
            return (1);
        str_exp[(*n_char)++] = str[(*i)++];
    }
    return (0);
}
