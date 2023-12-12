/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:18:46 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/12 12:32:15 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**ft_new_env(int len, int index, char **env, char *variable)
{
	int		pos_add;
	char	**new_env;

	if (!env)
		return (NULL);
	new_env = malloc(sizeof(*new_env) * (len + 2));
	new_env = env;
	if (!new_env)
		error_msg("failed malloc in new_env");
	pos_add = index;
	if (variable)
		new_env[len - 1] = variable;
	return (new_env[len] = NULL, new_env);
}

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
