/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:58 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/10 15:25:51 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return ;
}

char	error_arg_msg(char *msg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: exit : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit (255);
	}
	else if (i == 2)
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		exit (errno);
	}
	else if (i == 3)
	{
		ft_putstr_fd("minishell: export : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(" : not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	if (i == 5)
	{
		ft_putstr_fd("minishell: unset : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(" : not a valid identifier\n", STDERR_FILENO);
		return (0);		
	}
	return (1);
}

void	err_cd_msg(int i)
{
	ft_putstr_fd("minishell: cd : ", STDERR_FILENO);
	if (i == 1)
		ft_putstr_fd("build relative path\n", STDERR_FILENO);
	else if (i == 2)
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}