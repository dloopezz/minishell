/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:18:46 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/08 18:29:43 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap_env(char **envio, int i, int j)
{
	char	*tmp;

	tmp = envio[i];
	envio[i] = envio[j];
	envio[j] = tmp;
}

static char	*env_sort(char **env)
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
			if (ft_strcmp(env[j], env[j + 1] > 0))
				ft_swap_env(*env, i, j);
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

static int	check_name(char *str)
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

char	*search_var_in_env(char *variable, char **env)
{
	int	i;
	int	len;

	if (!env || !variable)
		return (NULL);
	len = ft_strlen(len);
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]) || (!ft_strncmp(variable, env[i], len)
				&& !ft_strncmp('=', env[i] + len, 1)))
			break ;
		i++;
	}
	if (env[i])
		return (env[i]);
	else
		return (NULL);
}

int	ft_matrix_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//!CUIDADO return con más de una función
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
		{
			error_msg("failed malloc");
			return (ft_free_arrows(new_env, i));
		}
	}
	return (new_env[len] = NULL, ft_free_arrows(env, -1), new_env);
}
//TODO finalizar función
char	*set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*tmp;

	pos = search_var_in_env(variable, *env);
	if (pos < 0)
	{
		pos = ft_matrix_len(*env);
		*env = ft_new_env(pos + 1, -1, *env);
		if (!(*env))
			return (NULL);
	}
	free(*env[pos]);
	if (!str)
		tmp = ft_strjoin(variable, NULL);
	else
		tmp = ft_strjoin(variable, '=');
	
}
//TODO finalizar función
int	exportvar(char *str, char ***env)
{
	char	*var;
	char	*name;

	name = *str;
	if (check_name(name))
		return (-1);
	str = ft_strchr(str, '=');
	if (str)
		*(str++) = '\0';
	var = search_var_in_env(name, *env);
	if (!var)
		
}
//TODO finalizar función
int	ft_export(char *token, char ***env)
{
	int		i;
	int		ret;
	char	*str;

	if (!*env)
		return (-1);
	if (!token || token[0] == NULL)
		return (show_env_sort(*env));
	else
	{
		ret = 0;
		i = -1;
		while (token[++i])
			ret += exportvar(token[i], env);
	}	

}