/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/07 16:27:13 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//# define FAILED_MALLOC			0b00000000000000000000001

int	ft_builtin(t_token *token, t_data *data)
{
	if (!token->type)
		return (0);
	if (ft_strncmp(token->arg[0], "cd", 2) == 0)
		return (ft_cd(token->type, data->envi));
	if (ft_strncmp(token->arg[0], "pwd", 3) == 0)
		return (ft_pwd);
	if (ft_strncmp(token->arg[0], "echo", 4) == 0)
		return (ft_echo(token->arg));
	if (ft_strncmp(token->arg[0], "unset", 5) == 0)
		return (ft_unset(token->arg[0], &data->envi));
	if (ft_strncmp(token->arg[0], "export", 6) == 0)
		return (ft_export(token->arg[0], &data->envi));
	if (ft_strncmp(token->arg[0], "exit", 4))
		return (ft_exit(token->arg, token->data));
}
