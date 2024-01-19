/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:03:50 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/19 14:37:08 by crtorres         ###   ########.fr       */
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

int	handle_quotes(char *str, int *len, char **env)
{
	if (str[0] == SQUOTES)
		return (process_squotes(str, len));
	else if (str[0] == DQUOTES)
		return (process_dquotes(str, len, env));
	return (0);
}
