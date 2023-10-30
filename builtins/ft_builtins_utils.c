/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:17:22 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/30 16:24:25 by crtorres         ###   ########.fr       */
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
	int	i;
	int	len;
	int	total_len;
	char *tmp;

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
		if ((ft_strcmp(variable, env[i]) == 0) || ((ft_strncmp(variable, env[i], len) == 0)
				&& (ft_strncmp("=", env[i] + len, 1) == 0)))
			return (i);
		i++;
	}
	return (-1);
}

char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*tmp;
	char	*tmporal;
	char	**new_env;

	new_env = malloc(sizeof(*env) * (ft_matrix_len(env) + 1));
	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		if (!str)
			tmp = ft_strjoin(variable, NULL);
		else
			tmp = ft_strjoin(variable, "=");
		if (!tmp)
			error_msg("failed tmp");
		if (!env)
			return (NULL);
		tmporal = ft_strjoin(tmp, str);
		env = ft_new_env(pos + 1, -1, env, tmporal);
		return (env);
	}
	else if (pos >= 0)
	{
			
		if (!str)
			tmp = ft_strjoin(variable, NULL);
		else
			tmp = ft_strjoin(variable, "=");
		if (!tmp)
			error_msg("failed malloc");
		env[pos] = ft_strjoin(tmp, str);
		if (!env[pos])
			error_msg("failed malloc");
	}
	//free(tmp);
	return (&env[pos]);
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
