/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/03 18:22:30 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	process_SQUOTES(char *str, int *len)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] != SQUOTES)
	{
		i++;
		(*len)++;
	}
	(*len)++;
	return (i);
}

int	process_DQUOTES(char *str, int *len, char **env)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] == '$')
		i += check_init_dollar(&str[i], len, NULL, env);
	if (str[i] == '\0')
		return (i);
	while (str[i] && str[i] != DQUOTES)
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
    while (str[*i] && str[*i] == '$')
        (*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
    if (str[*i] == '\0')
        return (1);
    while (str[*i] && str[*i] != DQUOTES)
    {
        while (str[*i] && str[*i] == '$')
            (*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
        if (str[*i] == '\0')
            return (1);
        str_exp[(*n_char)++] = str[(*i)++];
    }
    str_exp[(*n_char)++] = str[(*i)++];
    return (0);
}

int sing_quotes(char *str, int *i, int *n_char, char *str_exp)
{
	str_exp[(*n_char)++] = str[(*i)++];
	while (str[*i] && str[*i] != SQUOTES)
	{
		str_exp[(*n_char)++] = str[(*i)++];
		if (str[*i] == '\0')
			return (1);
	}
	str_exp[(*n_char)++] = str[(*i)++];
	return (0);
} */
int	process_SQUOTES(char *str, int *len)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] != SQUOTES)
	{
		if (str[i] == '\0')
			break;
		i++;
		(*len)++;
	}
	(*len)++;
	return (i);
}

int	process_DQUOTES(char *str, int *len, char **env)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] == '$')
		i += check_init_dollar(&str[i], len, NULL, env);
	if (str[i] == '\0')
		return (i);
	while (str[i] && str[i] != DQUOTES)
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
	while (str[*i] && str[*i] != DQUOTES)
	{
		if (str[*i] && str[*i] == '$' && str[*i + 1] != SQUOTES 
			&& str[*(i + 1)] != DQUOTES)
			(*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
		if (str[*i] == '\0')
			return (1);
		str_exp[(*n_char)++] = str[(*i)++];
	}
	return (0);
}
