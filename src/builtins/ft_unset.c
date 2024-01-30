/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:11:19 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/30 19:36:43 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**ft_rm_env_elem(int len, int index, char **env)
{
	char	**new_env;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * ft_matrix_len(env));
	i = 0;
	j = 0;
	while (j < len - 1)
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}	
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	if (i == index)
		free(env[i]);
	free(env);
	new_env[j] = NULL;
	return (new_env);
}

int	ft_unset(t_token *token, t_data *data)
{
	t_token	*aux;
	int		i;
	int		index;

	aux = token;
	if (!aux->args[1])
		return (0);
	if (ft_strchr(aux->args[1], '='))
		return (error_arg_msg(aux->args[1], 5));
	i = 0;
	while (aux->args && aux->args[i])
	{
		index = get_posvar_in_env(aux->args[i], data->envi);
		if (index >= 0 && *data->envi)
		{
			data->envi = ft_rm_env_elem(ft_matrix_len(data->envi),
					index, data->envi);
			// system("leaks -q minishell");
		}
		i++;
	}
	return (1);
}
