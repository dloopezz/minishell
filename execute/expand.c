/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/05 14:21:50 by crtorres         ###   ########.fr       */
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
			return (ft_strdup(env[i] + i + 1));
		}
		i++;
	}
	return (NULL);
}

/* char *ft_strcpy(char *dst, const char *src)
{
	return (ft_memmove(dst, src, ft_strlen(src) + 1));
} */

int	check_init_dollar(char *str, int *len, char *string, char **env)
{
	int		i;
	char 	*s;
	char 	*new;

	i = 1;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	s = ft_substr(s, i, i - 1);
	new = get_env(str, env);
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
	//free (new);
	//free (str);
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
		//printf("str[i] es: %c\n", str[i]);
		//sleep(2);
		if (str[i] && str[i] == DOUBLE_QUOTES)
		{
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
	//t_data *data;

	len = expandlen(str, env->envi);
	str_expand = ft_calloc(len +1, 1);	
	i = 0;
	n_char = 0;
	//printf("env es: %s\n", env->envi[i]);
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
			printf("entra\n");
			str_expand[n_char++] = str[i++];
			printf("str_bucle : %s\n", str_expand);
			printf("str[i] : %c\n", str[i]);
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
		printf("str : %s\n", str);
		str_expand[n_char++] = str[i++];
		printf("str_expand : %s\n", str_expand);
	}
	return (str_expand);
}

/* char *get_env_and_expand(char *str, t_data *env)
{
	int	i;
	char	*s;
	char	*new;

	i = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	s = ft_substr(str, i, i - 1);
	new = get_env(s, env);
	if (!new)
		return (ft_strjoin("$", s));
	return (new);
}

int expandlen(char *str, t_data *env)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '$')
			len += *get_env_and_expand(str + len + 1, env);
		else if (str[len] == SINGLE_QUOTES)
		{
			len++;
			while (str[len] && str[len] != SINGLE_QUOTES)
				len++;
			len++;
		}
		else if (str[len] == DOUBLE_QUOTES)
		{
			len++;
			while (str[len] && str[len] != DOUBLE_QUOTES)
				len++;
			len++;
		}
	}
	return (len);
}

char *ft_expand(char *str, t_data *env)
{
	int	len;
	char	*str_expand;

	len = expandlen(str, env);
	str_expand = ft_calloc(len + 1, 1);
	ft_strcpy(str_expand, str);
	return (str_expand);
} */
