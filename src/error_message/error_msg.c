/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:58 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/12 16:31:14 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		exit(255);
	}
	else if (i == 2)
	{
		ft_putstr_fd("minishell: exit : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (g_exit_code = 1, 1);
	}
	else if (i == 3)
	{
		ft_putstr_fd("minishell: export : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (g_exit_code = 1, 1);
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

int	error_syntax_msg(char *msg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (0);
}

void	exec_exit_error(int err, char *msg)
{
	char * err_str;
	
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err == 1)
	{
		err_str = strerror(errno);
		ft_putendl_fd(err_str, STDERR_FILENO);
		g_exit_code = errno;
	}
	else if (err == 2)
	{
		err_str = strerror(errno);
		ft_putendl_fd(err_str, STDERR_FILENO);
		g_exit_code = errno;
	}
	else if (err == 4)
		perror("no such file or directory :");
	else if (err == 5)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		perror(" ");
		g_exit_code = 1;
	}
	else if (err == 6)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
		g_exit_code = 127;
	}
	else if (err == 7)
		perror("here_doc error :");
	else if (err == 8)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		g_exit_code = 126;
	}
	return ;
}
