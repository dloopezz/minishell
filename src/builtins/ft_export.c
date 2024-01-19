/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:18:46 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/19 14:17:15 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	**env_sort(char **env)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (*env && env[len])
		len++;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				ft_swap_env(env, j, j + 1);
			j++;
		}
		i++;
	}
	return (env);
}

static char	show_env_sort(char **env, int fd)
{
	int	i;
	int	j;
	int	quotes;

	env = env_sort(env);
	i = 0;
	while (env && env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", fd);
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], fd);
		quotes = (env[i][j] == '=');
		if (env[i][j] == '=')
			ft_putchar_fd(env[i][j++], fd);
		if (quotes)
			ft_putchar_fd('"', fd);
		while (env[i][j])
			ft_putchar_fd(env[i][j++], fd);
		if (quotes)
			ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	return (1);
}

char	**ft_new_env(int len, char **env, char *variable)
{
	char	**new_env;

	if (!env)
		return (NULL);
	new_env = env;
	if (!new_env)
		error_arg_msg("failed malloc in new_env", 4);
	if (variable)
		new_env[len - 1] = variable;
	return (new_env[len] = NULL, new_env);
}

//! Solucion guarra para el caso de exportar sin signo igual
int	exportvar(char *str, char **env)
{
	char	*var;
	char	*name;

	name = str;
	if (check_name(name))
		return (-1);
	str = ft_strchr(str, '=');
	if (str)
		*(str++) = '\0';
	else
	{
		error_arg_msg("'='", 3);
		return (1);
	}
	var = search_var_in_env(name, env);
	if (!var)
		set_var_in_env(name, str, env);
	else if (str && var)
		set_var_in_env(name, str, env);
	return (1);
}

//TODO revisar que almacene mas de una variable en el env
int	ft_export(t_token *token, t_data *data, int fd)
{
	int		i;
	int		n_ret;

	if (!*data->envi)
		return (-1);
	if (!token || !token->args[1])
		return (show_env_sort(data->envi, fd));
	else
	{
		n_ret = 0;
		i = 0;
		while (token->args[++i])
			n_ret += exportvar(token->args[i], data->envi);
	}
	return (n_ret);
}
