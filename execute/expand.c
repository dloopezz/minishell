/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:07:15 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 16:35:29 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_env(char *str, t_data *env)
{
	int	i;
	int	len;
	len = ft_strlen(str);
	while (env->env_copy[i])
	{
		if (!ft_strncmp(env->env_copy[i], str, len))
		{
			return (ft_strdup(env->env_copy[i] + i + 1));
		}
		i++;
	}
	return (NULL);
}

int	check_init_dollar(char *str, int *len, char *string, t_data *env)
{
	int		i;
	char 	*s;
	char 	*new;
	int		j;

	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
		i++;
	s = ft_substr(s, i, i - 1);
	new = get_env(str, env);
	if (!*s)
	{
		ft_strcat
	}
}

int	expandlen(char *str, t_data *env)
{
	int	i;
	int	len;
<<<<<<< HEAD

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$')
			i += check_init_dollar(str[i], &len, NULL, env);
		if (str[i] == '\0')
			break ;
	}
}

char ft_expand(char *str, t_data *env)
{
	int		len;
	int		n_char;
	int		i;
	char	*str_expand;

	len = expandlen(str, env);
	str = ft_calloc(len +1, 1);
=======
	
	i = 0;
	len = 0;
	
}
