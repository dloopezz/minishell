/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:11:19 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/17 16:49:29 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_free_arrows(char **array, int number)
{
	int	i;

	i = 0;
	while (array && array[i] && (i < number || number < 0))
		free(array[i++]);
	if (array)
		free(array);
	return (NULL);
}

//TODO revisar mensajes de error en el futuro
char	**ft_rm_env_elem(int len, int index, char **env)
{
	int		i;
	int		ind_pos;
	char	**new_env;

	if (!env)
		return (NULL);
	ind_pos = 0;
	new_env = malloc(sizeof(*new_env) * (len + 1));
	if (!new_env)
		error_msg("new_env failed");
	i = -1;
	while (++i < len)
	{
		ind_pos += (i == index);
		if (env[i + ind_pos] != NULL)
			new_env[i] = ft_strdup(env[i + ind_pos]);
		else
		{
			new_env[i] = ft_strdup("");
			if (new_env[i] == NULL)
				return (error_msg("new_env failed"),
					ft_free_arrows(new_env, i), NULL);
		}
	}
	return (new_env[len] = NULL, new_env);
}

int	ft_unset(t_token *token, t_data *data)
{
	int	index;

	if (ft_strchr(token->args[1], '='))
		return (error_arg_msg(token->args[1], 5));
	while (token->args && token->args[1])
	{
		index = get_posvar_in_env(token->args[1], data->envi);
		if (index >= 0 && *data->envi)
			data->envi = ft_rm_env_elem(ft_matrix_len(data->envi),
					index, data->envi);
		token->args++;
	}
	return (1);
}
