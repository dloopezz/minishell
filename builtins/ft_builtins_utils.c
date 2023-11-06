/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:17:22 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/02 13:08:16 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap_env(char **envi, int i, int j)
{
	char	*tmp;

	tmp = envi[i];
	envi[i] = envi[j];
	envi[j] = tmp;
}

char	*search_shlvar_in_env(char *variable, char **env)
{
	int		i;
	int		len;
	int		total_len;
	char	*tmp;

	if (!env || !variable)
		return (NULL);
	len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]) || (!ft_strncmp(variable, env[i], len)
				&& !ft_strncmp("=", env[i] + len, 1)))
		{
			total_len = ft_strlen(env[i]);
			tmp = ft_substr(env[i], 6, total_len);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

char	*search_var_in_env(char *variable, char **env)
{
	int	i;
	int	len;

	if (!env || !variable)
		return (NULL);
	len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]) || (!ft_strncmp(variable, env[i], len)
				&& !ft_strncmp("=", env[i] + len, 1)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	get_posvar_in_env(char *variable, char **env)
{
	int		i;
	int		len;

	if (!env || !variable)
		return (-1);
	len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if ((ft_strcmp(variable, env[i]) == 0)
			|| ((ft_strncmp(variable, env[i], len) == 0)
				&& (ft_strncmp("=", env[i] + len, 1) == 0)))
			return (i);
		i++;
	}
	return (-1);
}

int	check_name(char *str)
{
	char	*begin;

	begin = str;
	while (ft_isalpha(*str) || *str == '_')
		str++;
	if (str != begin)
	{
		while (ft_isalnum(*str) || *str == '_')
			str++;
		if (*str == '\0' || *str == '=')
			return (0);
	}
	error_arg_msg("export builtin", 3);
	return (1);
}
