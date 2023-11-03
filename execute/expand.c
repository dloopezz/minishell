/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/03 18:04:37 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			return (ft_strdup(env[i] + len));
		i++;
	}
	return (NULL);
}

char	*quote_var(char *new)
{
	int		i;
	int		j;
	char	*new_quoted;

	i = 0;
	j = 0;
	new_quoted = ft_calloc(1, ft_strlen(new) + 3); //+2 para las quotes
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
	if (!new && !str[i])
	{
		new = "";
		new = quote_var(new);
	}
	else if (!new)
	{
		if (str[i] == SQUOTES && str[i + 1] != DQUOTES)
			process_SQUOTES(str + i, len);
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
	return (free (new), i);
}

int	expandlen(char *str, char **env)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '$' && str[i + 1] != SQUOTES)
			i += check_init_dollar(&str[i], &len, NULL, env);
		if (str[i] == '\0')
			break ;
		if (str[i] == SQUOTES)
			i += process_SQUOTES(&str[i], &len);
		else if (str[i] == DQUOTES)
			i += process_DQUOTES(&str[i], &len, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char *ft_expand(char *str, t_data *env)
{
	int		n_char;
	int		i;
	char	*str_expand;
	int		d_mode;
	//int		s_mode;
	int		single_mode;

	n_char = 0;
	d_mode = 0;
	//s_mode = 0;
	single_mode  = 0;
	str_expand = ft_calloc(expandlen(str, env->envi) + 1, 1);
	i = 0;
	while (str[i])
	{
		if (str[i +1] && str[i] == '$' && (str[i + 1] == DQUOTES))
		{
			d_mode = !d_mode;
			i++;
		}
		else if (str[i +1] && str[i] == '$' && str[i + 1] == SQUOTES)
		{
				single_mode = !single_mode;
			i++;
		}
		if (str[i] == '$' && (!single_mode/*  || !d_mode || !s_mode */))
			i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
		else if (str[i] == SQUOTES)
		{
			single_mode = !single_mode;
			str_expand[n_char++] = str[i++];













			
		}
		else if (str[i] == DQUOTES && !d_mode)
		{
			if (doub_quotes(str, &i, &n_char, str_expand, env))
				break;
		}
		else
		{
			str_expand[n_char++] = str[i++];
			if (str[i] == '$' && str[i + 1] == '?')
				return (ft_itoa(env->exit_code));
		}
    }
	return (str_expand);
}
//!revisar lineas 105 y 106 para el código de error en un futuro