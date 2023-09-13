/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:18:46 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 16:38:29 by crtorres         ###   ########.fr       */
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
				ft_swap_env(env, i, j);
			j++;
		}
		i++;
	}
	return (env);
}

static char	show_env_sort(char **env)
{
	int	i;
	int	j;
	int	quotes;

	env = env_sort(env);
	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], STDOUT_FILENO);
		quotes = (env[i][j] == '=');
		if (env[i][j] == '=')
			ft_putchar_fd(env[i][j++], STDOUT_FILENO);
		if (quotes)
			ft_putchar_fd('"', STDOUT_FILENO);
		while (env[i][j])
			ft_putchar_fd(env[i][j++], STDOUT_FILENO);
		if (quotes)
			ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (1);
}

char	**ft_new_env(int len, int index, char **env)
{
	int		i;
	int		pos_rem;
	char	**new_env;

	if (!env)
		return (NULL);
	new_env = malloc(sizeof(*new_env) * (len + 1));
	if (!new_env)
		error_msg("failed malloc in new_env");
	pos_rem = 0;
	i = -1;
	while (++i < len)
	{
		pos_rem += (i == index);
		if (env[i + pos_rem])
			new_env[i] = ft_strdup(env[i + pos_rem]);
		else
			new_env[i] = ft_strdup("");
		if (!new_env[i])
			return (error_msg("failed malloc"), ft_free_arrows(new_env, i));
	}
	new_env[len] = NULL;
	ft_free_arrows(env, -1);
	return (new_env);
}

int	exportvar(char *str, char ***env)
{
	char	*var;
	char	*name;

	name = str;
	if (check_name(name))
		return (-1);
	str = ft_strchr(str, '=');
	if (str)
		*(str++) = '\0';
	var = search_var_in_env(name, *env);
	if (!var)
		set_var_in_env(name, str, *env);
	else if (str && var)
		set_var_in_env(name, str, *env);
	return (1);
}

int	ft_export(char **token, char ***env)
{
	int		i;
	int		n_ret;

	//printf("token es %s\n", token);
	if (!*env)
		return (-1);
	if (!token || !token[0])
		return (show_env_sort(*env));
	else
	{
		n_ret = 0;
		i = -1;
		while (token[++i])
			n_ret += exportvar(token[i], env);
	}	
	return (n_ret);
}
