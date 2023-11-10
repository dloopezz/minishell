/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/10 12:37:42 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_squotes(char *str, int *len)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] != SQUOTES)
	{
		if (str[i] == '\0')
			break;
		// printf("STR[i]: |%c|\n", str[i]);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	i++;
	(*len) += i; //habia un +1
	return (i);
}

int	process_dquotes(char *str, int *len, char **env)
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
		if (str[*i] == SQUOTES)
			str_exp[(*n_char)++] = str[(*i)++];
		else if (str[*i] && str[*i] == '$' && str[*i + 1] != SQUOTES 
			&& str[*(i) + 1] != DQUOTES)
			(*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
		else if (str[*i] == '\0')
			return (1);
		else
			str_exp[(*n_char)++] = str[(*i)++];
	}
	if (str[*i] == DQUOTES)
			str_exp[(*n_char)++] = str[(*i)++];
	// printf("STREXP: |%s|\n", str_exp);
	return (0);
}

int sing_quotes(char *str, int *i, int *n_char, char *str_exp, t_data *env)
{
	str_exp[(*n_char)++] = str[(*i)++];
	if (str[*i] == '\0')
		return (1);
	while (str[*i] && str[*i] != SQUOTES)
	{
		str_exp[(*n_char)++] = str[(*i)++];
	}
	str_exp[(*n_char)++] = str[(*i)++];
	return (0);
	if (str[*i] && str[*i - 1] && str[*i] == '$' && str[*i + 1] != SQUOTES 
		&& str[*(i) + 1] != DQUOTES)
	{
		(*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
		// printf("STR[i]: |%c|n", str[*i -1]);	
	}
	// if (str[*i] == SQUOTES)
	// 	return (1);
	if (str[*i] == '\0')
		return (1);
	return (0);
}
