/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/09 16:39:33 by crtorres         ###   ########.fr       */
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
	free (new);
	return (i);
}

int	expandlen(char *str, char **env)
{
	int	i = 0;
	int	len = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], &len, NULL, env);
		if (str[i] == '\0')
			break;
		if (str[i] == SINGLE_QUOTES)
			i += process_single_quotes(&str[i], &len);
		else if (str[i] == DOUBLE_QUOTES)
			i += process_double_quotes(&str[i], &len, env);
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
    int n_char = 0;
    int i = 0;
    char *str_expand; 
	
	str_expand = ft_calloc(expandlen(str, env->envi) + 1, 1);
    while (str[i])
    {
        if (str[i] == '$')
            i += check_init_dollar(&str[i], &n_char, str_expand, env->envi);
        else if (str[i] == SINGLE_QUOTES)
        {
            if (sing_quotes(str, &i, &n_char, str_expand))
                break;
        }
        else if (str[i] == DOUBLE_QUOTES)
        {
            if (doub_quotes(str, &i, &n_char, str_expand, env))
                break;
        }
        else
            str_expand[n_char++] = str[i++];
    }
    return str_expand;
}
