/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:16:58 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/28 12:21:34 by dlopez-s         ###   ########.fr       */
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

void	create_new_string(char *string, char *s, int *len, char *new)
{
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
	create_new_string(string, s, len, new);
	return (free(s), free(new), i);
}

// int	handle_quotes(char *str, int *len, char **env)
// {
// 	if (str[0] == SQUOTES)
// 		return (process_squotes(str, len));
// 	else if (str[0] == DQUOTES)
// 		return (process_dquotes(str, len, env));
// 	return (0);
// }
