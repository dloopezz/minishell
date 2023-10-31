/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:11:19 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/31 15:34:55 by crtorres         ###   ########.fr       */
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
	new_env = malloc(sizeof(*new_env) * (len + 1));
	if (!new_env)
		error_msg("new_env failed");
	ind_pos = 0;
	i = -1;
	while (++i < len)
	{
		if (i == index)
		{
			free (env[i]);
			ind_pos++;
		}
		else
		{
			new_env[i - ind_pos] = ft_strdup(env[i]);
			if (new_env == NULL)
				return (error_msg("new_env failed"), NULL);
		}
	}
	return (new_env[len - ind_pos] = NULL, new_env);
}

int	ft_unset(t_token *token, t_data *data)
{
	int	index;

		if (!token->args[1])
		return (0);
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
