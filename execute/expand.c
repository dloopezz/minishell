/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/05 16:05:17 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_env(char *str, char **env)
{
	int	i;
	int	len;
	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len))
		{
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	return (NULL);
}

int	check_init_dollar(char *str, int *len, char *string, char **env)
{
	int		i;
	char 	*s;
	char 	*new;

	i = 1;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	s = ft_substr(str, 1, i - 1);
	new = get_env(s, env);
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
	printf("i en$ es: %d\n", i);
	free (new);
	return (i);
}

int	expandlen(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], &len, NULL, env);
		if (str[i] == '\0')
			break ;
		if (str[i] && str[i] == SINGLE_QUOTES)
		{
			i++;
			len++;
			while (str[i] && str[i] != SINGLE_QUOTES)
			{
				i++;
				len++;
				if (str[i] == '\0')
					break ;
			}
			len++;
			i++;
		}
		if (str[i] && str[i] == DOUBLE_QUOTES)
		{
			len++;
			i++;
			while (str[i] && str[i] == '$')
				i += check_init_dollar(&str[i], &len, NULL, env);
			if (str[i] == '\0')
				break ;
			while (str[i] && str[i] != DOUBLE_QUOTES)
			{
				while (str[i] && str[i] == '$')
					i += check_init_dollar(&str[i], &len, NULL, env);
				if (str[i] == '\0')
					break ;
				len++;
				i++;
			}
			if (str[i] == '\0')
				break ;
			len++;
			i++;
		}
		if (str[i] == '\0')
			break ;
		len++;
		i++;
	}
	return (len);
}

char *ft_expand(char *str, t_data *env)
{
	int		len;
	int		n_char;
	int		i;
	char	*str_expand;

	len = expandlen(str, env->envi);
	str_expand = ft_calloc(len + 1, 1);	
	i = 0;
	n_char = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
		if (str[i] == '\0')
			break ;
		if (str[i] && str[i] == SINGLE_QUOTES)
		{
			str_expand[n_char++] = str[i++];
			while (str[i] && str[i] != SINGLE_QUOTES)
			{
				str_expand[n_char++] = str[i++];
				if (str[i] == '\0')
					break ;
			}
			str_expand[n_char++] =str[i++];
		}
		if (str[i] && str[i] == DOUBLE_QUOTES)
		{
			str_expand[n_char++] = str[i++];
			while (str[i] && str[i] == '$')
				i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
			if (str[i] == '\0')
				break ;
			while (str[i] && str[i] != DOUBLE_QUOTES)
			{
				while (str[i] && str[i] == '$')
					i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
				if (str[i] == '\0')
					break ;
				str_expand[n_char++] = str[i++];
			}
			str_expand[n_char++] = str[i++];
		}
		if (str[i] == '\0')
			break ;
		str_expand[n_char++] = str[i++];
	}
	return (str_expand);
}
