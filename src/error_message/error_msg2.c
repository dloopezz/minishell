/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:18:12 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/27 21:04:52 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	err_cd_msg(char *msg, int i)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (i == 1)
		ft_putstr_fd("build relative path\n", STDERR_FILENO);
	else if (i == 2)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_exit_code = 1;
	}
	else if (i == 3)
	{
		ft_putstr_fd("HOME is not set\n", STDERR_FILENO);
		g_exit_code = 1;
	}
	else if (i == 4)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}

int	err_syntax(char *msg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (0);
}
