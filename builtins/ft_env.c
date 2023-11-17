/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:20:32 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/15 16:02:22 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_data *data, t_token *tokens)
{
	int	i;

	if (tokens->args[1])
		return (error_arg_msg(NULL, 2));
	i = -1;
	while (data->envi[++i] && data->envi[i] != '\0')
		printf("%s\n", data->envi[i]);
	return (0);
}
