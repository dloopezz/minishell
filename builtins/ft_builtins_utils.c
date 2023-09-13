/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:17:22 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 17:50:28 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap_env(char **envi, int i, int j)
{
	char	*tmp;

	//printf("entra\n");
	tmp = envi[i];
	envi[i] = envi[j];
	envi[j] = tmp;
}

char	*search_var_in_env(char *variable, char **env)
{
	int		i;
	int	len;

	if (!env || !variable)
		return (NULL);
	len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]) || (!ft_strncmp(variable, env[i], len)
				&& !ft_strncmp("=", env[i] + len, 1)))
			break ;
		i++;
	}
	if (env[i])
		return (env[i]);
	else
		return (NULL);
}

int	get_posvar_in_env(char *variable, char **env)
{
	int		i;
	int	len;

	if (!env || !variable)
		return (-1);
	len = ft_strlen(variable);
	i = 1;
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]))
			break ;
		printf("posicion en el env: %d\n", i);
		i++;
	}
	printf("posicion en env[i]: %s\n", env[i]);
	if (env[i])
		return (i);
	else
		return (-1);
}

int	ft_matrix_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*tmp;

	pos = get_posvar_in_env(variable, env);
	printf("posicion : %d\n", pos);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		env = ft_new_env(pos + 1, -1, env);
		if (!env)
			return (NULL);
	}
	//free(env[pos]);
	if (!str)
		tmp = ft_strjoin(variable, NULL);
	else
		tmp = ft_strjoin(variable, "=");
	if (!tmp)
		error_msg("failed malloc");
	
	env[pos] = ft_strjoin(tmp, str);
	if (!env[pos])
		error_msg("failed malloc");
	//free(tmp);
	printf("env[pos]%s\n", env[pos]);
	return (env[pos]);
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
