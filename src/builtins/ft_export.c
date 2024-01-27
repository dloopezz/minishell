/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:18:46 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/26 17:25:47 by dlopez-s         ###   ########.fr       */
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
	new_env = (char **)malloc(sizeof(char *) * (ft_matrix_len(env) + 2));
	len = 0; //nosirve
	int i = 0;
	int len_mtx = ft_matrix_len(env);
	while (i < len_mtx)
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
	
	if (variable)
		new_env[i++] = ft_strdup(variable);
	new_env[i] = NULL;

	if (!new_env)
		error_arg_msg("failed malloc in new_env", 4);
	return (new_env);
}

//! Solucion guarra para el caso de exportar sin signo igual
char **exportvar(char *str, char **env, int *n_ret)
{
	char	*var;
	char	*name;

	name = str;
	if (check_name(name))
	{
		*n_ret = -1;
		return (env);
	}
	str = ft_strchr(str, '=');
	if (str)
		*(str++) = '\0';
	else
	{
		error_arg_msg("'='", 3);
		*n_ret = 1;
		return (env);
	}
	var = search_var_in_env(name, env);
	if (!var)
		env = set_var_in_env(name, str, env);
	else if (str && var)
		env = set_var_in_env(name, str, env);
	*n_ret = 1;
	return (env);
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
			data->envi = exportvar(token->args[i], data->envi, &n_ret);
	}

	
	// i = 0;
	// int len_mtx = ft_matrix_len(data->envi);
	// while (i++ < len_mtx)
	// 	printf("ENV: |%s - %p|\n", data->envi[i], data->envi[i]);

	return (n_ret);
}
