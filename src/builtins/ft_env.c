/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:20:32 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/18 11:21:38 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_env(t_data *data, t_token *tokens, int fd)
{
	int	i;

	if (tokens->args[1])
		return (error_arg_msg(NULL, 2));
	i = -1;
	while (data->envi[++i] && data->envi[i] != '\0')
		ft_putendl_fd(data->envi[i], fd);
	return (0);
}
