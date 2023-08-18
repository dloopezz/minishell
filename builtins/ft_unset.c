/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:11:19 by crtorres          #+#    #+#             */
/*   Updated: 2023/08/17 17:53:52 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_index_env(char *variable, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	if (!variable || !env)
		return (-1);
	while (env[i])
	{
		if (!ft_strcmp(variable, env[i]) || !ft_strncmp(variable, env[i], len)
			&& !ft_strncmp("=", env[i] + len, 1))
			break;
		i++;
	}
	if (env[i])
		return (i);
	else
		return (-1);
}

void	*ft_free_arrows(char **array, int number)
{
	int	i;

	i = 0;
	while (array[i] && (i < number | number < 0))
		free(array[i++]);
	if (array)
		free(array);
	return (NULL);
}

char	ft_rm_env_elem(int len, int index, char **env)
{
	int		i;
	int		ind_pos;
	char	**new_env;

	ind_pos = 0;
	new_env = malloc(sizeof(*new_env) * (len + 1));
	if (!new_env)
		return (/* poner funcion de mensaje de error */error);
	if (!env)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		ind_pos += (i == index);
		if (env[i + ind_pos])
			new_env[i] = ft_strdup(env[i + ind_pos]);
		else
			new_env[i] = ft_strdup("");
		if (new_env[i] == NULL)
		{
			mensaje error;
			return (ft_free_arrows(new_env, i));
		}
	}
	new_env[len] = '\0';
	ft_free_arrows(env, i);
	return (new_env);
}

int	ft_unset(char **pointer, char **env)
{
	int	index;

	while (pointer && *pointer)
	{
		index =ft_index_env(*pointer, *env);
		if (index >= 0 && *env)
			*env = ft_rm_env_elem(ft_strlen(*env) - 1, index, *env);
		pointer++;
	}
	return (1);
}