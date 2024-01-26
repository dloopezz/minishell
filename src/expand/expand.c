/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/19 16:34:22 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_init_dollar(char *str, int *len, char *string, char **env)
{
	int		i;
	char	*s;
	char	*new;

	i = 1;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	s = ft_substr(str, 1, i - 1);
	new = get_env(s, env);
	if (!new)
	{
		if (str[i] == SQUOTES && str[i + 1] != DQUOTES)
			process_squotes(str + i, len);
	}
	else
		new = quote_var(new);
	create_new_string(string, s, len, new);
	return (free (s), free(new), i);
}

int	expandlen(char *str, char **env)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	int str_len = ft_strlen(str);
	while (i <= str_len)
	{
		if (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], &len, NULL, env);
		else if (str[i] == '~')
		{
			len += ft_strlen(get_home(env)) + 2;
			i++;
		}
		else if (str[i] == SQUOTES || str[i] == DQUOTES)
			i += handle_quotes(&str[i], &len, env);
		else if (str[i] == '\0')
			break ;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	handle_no_dollar(char *str, int *i, int *n_char, t_data *data)
{
	if (str[(*i) + 1] && str[*i] == '$' && (str[(*i) + 1] == DQUOTES))
		(*i)++;
	else if (str[*i] == '~' && !ft_isalnum(str[(*i) + 1]))
	{
		if (str[(*i) + 1] && str[(*i) + 1] == '~')
			while (str[*i] && str[*i] == '~')
				data->l_exp[*n_char++] = str[*i++];
		else
			data->l_exp = virgula_expand(data->l_exp, n_char, data);
	}
	else if (str[(*i) + 1] && str[*i] == '$' && str[(*i) + 1] == SQUOTES)
		(*i)++;
}

int	handle_with_dollar(char *str, int *i, int *n_char, t_data *data)
{
	if (str[*i] && str[*i] == '$')
	{
		*i += check_init_dollar(&str[*i], n_char, data->l_exp, data->envi);
	}
	else if (str[*i] && str[*i] == SQUOTES)
	{
		if (sing_quotes(i, n_char, data->l_exp, data))
			return (0);
	}
	else if (str[*i] && str[*i] == DQUOTES)
	{
		if (doub_quotes(i, n_char, data->l_exp, data))
			return (0);
	}
	else
	{
		if (str[*i] == '~' && !ft_isalnum(str[*i + 1]))
			(*i)++;
		else
			data->l_exp[(*n_char)++] = str[(*i)++];
		if (str[*i - 1] == '\0')
			return (0);
	}
	return (1);
}

char	*ft_expand(t_data *data, char *str)
{
	int		n_char;
	int		i;

	n_char = 0;
	data->l_exp = ft_calloc(expandlen(str, data->envi) + 1, 1);
	printf("LEN: %d\n", expandlen(str, data->envi));
	i = 0;
	while (str[i])
	{
		handle_no_dollar(str, &i, &n_char, data);
		if (!handle_with_dollar(str, &i, &n_char, data))
			break ;
	}
	return (free (str), data->l_exp);
}
