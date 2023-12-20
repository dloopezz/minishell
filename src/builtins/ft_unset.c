/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:11:19 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/20 12:48:51 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (!env || index < 0 || index >= len)
		return (env);
	while (index < len - 1)
	{
		env[index] = env[index + 1];
		index++;
	}
	env[len - 1] = NULL;
	return (env);
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
			data->envi = ft_rm_env_elem(ft_matrix_len(data->envi),
					index, data->envi);
		i++;
	}
	return (1);
}
