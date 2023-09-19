/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:46:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 16:29:10 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/minishell.h"

 int	ft_env(t_data *data, t_token *tokens)
 {
	int	i;

	if (tokens->args[1])
		return (error_arg_msg(NULL, 2));
	i = 0;
	while (data->envi[i])
	{
		printf("%s\n", data->envi[i]);
		i++;
	}
	return (0);
 }
 