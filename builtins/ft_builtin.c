/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/06 17:27:47 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin(t_token *token, t_data *data)
{
	if (!token->type)
		return (0);
	if (ft_strncmp(token->type, "cd", 2) == 0)
		return (ft_cd(token->type, data->envi));
	if (ft_strncmp(token->type, "pwd", 3) == 0)
		return (ft_pwd);
	if (ft_strncmp(token->type, "echo", 4) == 0)
		return (ft_echo(token->data));
	if (ft_strncmp(token->type, "unset", 5) == 0)
		return (ft_unset(token->type, &data->envi));
	if (ft_strncmp(token->type, "export", 6) == 0)
		return (); //!añadir bultin_export 
	if (ft_strncmp(token->type, "exit", 4))
		return (ft_exit(token->type, token->data));
}