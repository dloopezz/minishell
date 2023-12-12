/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/12 15:01:23 by dlopez-s         ###   ########.fr       */
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
		{
			len++;
			i++;
		}
	}
	return (len);
}

/* int	handle_dollar(char *str, int *n_char, char *str_expand, t_data *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += check_init_dollar(&str[i], n_char, str_expand, env->envi);
		else if (str[i] == SQUOTES)
		{
			if (sing_quotes(str, &i, n_char, str_expand, env))
				return (i);
		}
		else if (str[i] == DQUOTES)
		{
			if (doub_quotes(str, &i, n_char, str_expand, env))
				return (i);
		}
		else
		{
			if (str[i] == '\0')
				break;
			if (str[i] == '~')
					i++;
			else
			str_expand[(*n_char)++] = str[i++];
			if (*n_char >= (int)ft_strlen(str_expand))
    			return (i);
			if (str[i] == '$' && str[i + 1] == '?')
				return (i);
		}
	}
	return (i);
}

char *ft_expand(char *str, t_data *env)
{
	int		n_char;
	int		i;
	char	*str_expand;

	n_char = 0;
	str_expand = ft_calloc(expandlen(str, env->envi) + 1, 1);
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && (str[i + 1] == DQUOTES))
			i++;
		else if (str[i] == '~')
		{
			if (str[i + 1] && str[i + 1] == '~')
				while (str[i] && str[i] == '~')
					str_expand[n_char++] = str[i++];
			else
				str_expand = virgula_expand(str_expand, &n_char, env);
		}
		else if (str[i + 1] && str[i] == '$' && str[i + 1] == SQUOTES)
			i++;
		i = handle_dollar(&str[i], &n_char, str_expand, env);
	}
	return (str_expand);
} */

char *ft_expand(char *str, t_data *env)
{
	int		n_char;
	int		i;
	char	*str_expand;

	n_char = 0;
	str_expand = ft_calloc(expandlen(str, env->envi) + 1, 1);
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && (str[i + 1] == DQUOTES))
			i++;
		else if (str[i] == '~' && !ft_isalnum(str[i+1]))
		{
			if (str[i+ 1] && str[i+ 1] == '~')
				while (str[i] && str[i] == '~')
					str_expand[n_char++] = str[i++];
			else
				str_expand = virgula_expand(str_expand, &n_char, env);
		}
		else if (str[i + 1] && str[i] == '$' && str[i + 1] == SQUOTES)
			i++;
		if (str[i] == '$')
			i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
		else if (str[i] == SQUOTES)
		{
			if (sing_quotes(str, &i, &n_char, str_expand, env))
				break;
		}	
		else if (str[i] == DQUOTES)
		{
			if (doub_quotes(str, &i, &n_char, str_expand, env))
				break;
		}
		else
		{
			if (str[i] == '~' && !ft_isalnum(str[i+1]))
				i++;
			else
				str_expand[n_char++] = str[i++];
			if (str[i -1] == '\0')
				break ;
			/* if (str[i] == '$' && str[i + 1] == '?')
				return (ft_itoa(env->exit_code)); */
		}
	}
	return (str_expand);
}

//!revisar lineas 105 y 106 para el código de error en un futuro
//! REPARAR FUNCION HANDLE_DOLLAR PARA QUE FUNCIONE SIN BUFFER OVERFLOW EN EL CASO DE '~~' Y PODER USARLAS