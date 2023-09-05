/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/05 17:17:04 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		return (ft_cd(cmd->cmd, data->envi));
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd);
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		return (ft_echo(cmd->arg));
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		return (ft_unset(cmd->cmd, &data->envi));
	if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		return (); //!añadir bultin_export 
	if (ft_strncmp(cmd->cmd, "exit", 4))
		return (); //!añadir builtin_exit
}