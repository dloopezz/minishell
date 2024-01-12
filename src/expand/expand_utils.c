/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/11 18:13:16 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	process_squotes(char *str, int *len)
{
	int	i;

	i = 1;
	(*len)++;
	while (str[i] && str[i] != SQUOTES)
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	if (str[i] == '\0')
	{
		*len = i;
		return (i);
	}
	i++;
	(*len) += i;
	return (i);
}

int	process_dquotes(char *str, int *len, char **env)
{
	int	i;

	i = 1;
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

int	doub_quotes(int *i, int *n_char, char *str_exp, t_data *data)
{
	str_exp[(*n_char)++] = data->line[(*i)++];
	while (data->line[*i] && data->line[*i] != DQUOTES)
	{
		if (data->line[*i] == SQUOTES)
			str_exp[(*n_char)++] = data->line[(*i)++];
		else if (data->line[*i] && data->line[*i] == '$'
			&& data->line[*i + 1] != SQUOTES && data->line[*(i) + 1] != DQUOTES)
			(*i) += check_init_dollar(&data->line[*i], n_char, str_exp,
					data->envi);
		else if (data->line[*i] == '\0')
			return (1);
		else
			str_exp[(*n_char)++] = data->line[(*i)++];
	}
	if (data->line[*i] == DQUOTES)
		str_exp[(*n_char)++] = data->line[(*i)++];
	return (0);
}

int	sing_quotes(int *i, int *n_char, char *str_exp, t_data *data)
{
	str_exp[(*n_char)++] = data->line[(*i)++];
	if (data->line[*i] == '\0')
		return (1);
	while (data->line[*i] && data->line[*i] != SQUOTES)
	{
		str_exp[(*n_char)++] = data->line[(*i)++];
	}
	if (data->line[*i] && data->line[*i] == SQUOTES)
		str_exp[(*n_char)++] = data->line[(*i)++];
	return (0);
	if (data->line[*i] && data->line[*i - 1] && data->line[*i] == '$'
		&& data->line[*i + 1] != SQUOTES && data->line[*(i) + 1] != DQUOTES)
		(*i) += check_init_dollar(&data->line[*i], n_char, str_exp, data->envi);
	if (data->line[*i] == '\0')
		return (1);
	return (0);
}

char	*virgula_expand(char *str_exp, int *n_char, t_data *env)
{
	char	*home;
	int		i;

	i = 0;
	home = get_home(env->envi);
	str_exp[(*n_char)++] = DQUOTES;
	while (home[i])
		str_exp[(*n_char)++] = home[i++];
	str_exp[(*n_char)++] = DQUOTES;
	// free (home);
	return (str_exp);
}
