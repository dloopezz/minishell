/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/18 12:30:52 by crtorres         ###   ########.fr       */
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
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "expand.c", 42, new_quoted); //LEAKS
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
	return (free(new), i);
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
		{
			i += process_squotes(&str[i], &len);
		}
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

char	*ft_expand(t_data *data)
{
	int		n_char;
	int		i;
	char	*str_expand;

	n_char = 0;
	str_expand = ft_calloc(expandlen(data->line, data->envi) + 1, 1);
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "expand.c", 124, str_expand); //LEAKS
	i = 0;
	while (data->line[i])
	{
		if (data->line[i + 1] && data->line[i] == '$' && (data->line[i + 1] == DQUOTES))
			i++;
		else if (data->line[i] == '~' && !ft_isalnum(data->line[i + 1]))
		{
			if (data->line[i + 1] && data->line[i + 1] == '~')
				while (data->line[i] && data->line[i] == '~')
					str_expand[n_char++] = data->line[i++];
			else
				str_expand = virgula_expand(str_expand, &n_char, data);
		}
		else if (data->line[i + 1] && data->line[i] == '$' && data->line[i + 1] == SQUOTES)
			i++;
		if (data->line[i] == '$')
			i += check_init_dollar(&data->line[i], &n_char, str_expand, data->envi);
		else if (data->line[i] == SQUOTES)
		{
			if (sing_quotes(&i, &n_char, str_expand, data))
				break ;
		}
		else if (data->line[i] == DQUOTES)
		{
			if (doub_quotes(&i, &n_char, str_expand, data))
				break ;
		}
		else
		{
			if (data->line[i] == '~' && !ft_isalnum(data->line[i + 1]))
				i++;
			else
				str_expand[n_char++] = data->line[i++];
			if (data->line[i - 1] == '\0')
				break ;
		}
	}
	// free(data->line);
	return (str_expand);
}
