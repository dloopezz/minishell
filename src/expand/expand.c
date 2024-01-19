/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/18 16:53:20 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_env(char *str, char **env)
{
	int		i;
	int		len;
	char	*str1;

	str1 = ft_strjoin(str, "=");
	len = ft_strlen(str1);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str1, len))
		{
			free (str1);
			return ((env[i] + len));
		}
		i++;
	}
	free (str1);
	return (NULL);
}

char	*quote_var(char *new)
{
	int		i;
	int		j;
	char	*new_quoted;

	i = 0;
	j = 0;
	new_quoted = ft_calloc(1, ft_strlen(new) + 3);
	if (!new_quoted)
		return (NULL);
	new_quoted[j++] = DQUOTES;
	while (new[i])
		new_quoted[j++] = new[i++];
	new_quoted[j++] = DQUOTES;
	return (new_quoted);
}

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
	if (!*s)
	{
		ft_strcat(string, "$");
		*len += 1;
	}
	if (new)
	{
		*len += ft_strlen(new);
		ft_strcat(string, new);
	}
	return (free (s), free(new), i);
}

int	expandlen(char *str, char **env)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], &len, NULL, env);
		else if (str[i] == '~')
		{
			len += ft_strlen(get_home(env)) + 2;
			i++;
		}
		else if (str[i] == SQUOTES)
			i += process_squotes(&str[i], &len);
		else if (str[i] == DQUOTES)
			i += process_dquotes(&str[i], &len, env);
		else if (str[i] == '\0')
			break ;
		else
			len++;
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
		{
			data->l_exp = virgula_expand(data->l_exp, n_char, data);
		}
	}
	else if (str[(*i) + 1] && str[*i] == '$' && str[(*i) + 1] == SQUOTES)
		(*i)++;
}

/* int	handle_with_dollar(char *str, int *i, int *n_char, t_data *data)
{
	if (str[*i] == '$')
		*i += check_init_dollar(&str[*i], n_char, data->l_exp, data->envi);
	else if (str[*i] == SQUOTES)
	{
		if (sing_quotes(i, n_char, data->l_exp, data))
			return (0);
	}
	else if (str[*i] == DQUOTES)
	{
		if (doub_quotes(i, n_char, data->l_exp, data))
			return (0);
	}
	else
	{
		if (str[*i] == '~' && !ft_isalnum(str[*i + 1]))
			(*i)++;
		else
			data->l_exp[*n_char++] = str[*i++];
		if (str[*i - 1] == '\0')
			return (0);
	}
	return (1);
} */

char	*ft_expand(t_data *data, char *str)
{
	int		n_char;
	int		i;

	n_char = 0;
	data->l_exp = ft_calloc(expandlen(str, data->envi) + 1, 1);
	i = 0;
	while (str[i])
	{
		handle_no_dollar(str, &i, &n_char, data);
		if (str[i] == '$')
			i += check_init_dollar(&str[i], &n_char, data->l_exp, data->envi);
		else if (str[i] == SQUOTES)
		{
			if (sing_quotes(&i, &n_char, data->l_exp, data))
				break ;
		}
		else if (str[i] == DQUOTES)
		{
			if (doub_quotes(&i, &n_char, data->l_exp, data))
				break ;
		}
		else
		{
			if (str[i] == '~' && !ft_isalnum(str[i + 1]))
				i++;
			else
				data->l_exp[n_char++] = str[i++];
			if (str[i - 1] == '\0')
				break ;
		}
	}
	return (free (str), data->l_exp);
}
