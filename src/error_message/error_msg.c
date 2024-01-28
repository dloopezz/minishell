/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:58 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/28 01:58:57 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	error_msg(char *msg, int i)
{
	if (i == 4)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (g_exit_code = 1, 1);
	}
	else if (i == 5)
	{
		ft_putstr_fd("minishell: unset : ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(" : not a valid identifier\n", STDERR_FILENO);
		return (g_exit_code = 1, 0);
	}
	return (1);
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
	else if (i == 4 || i == 5)
		error_msg(msg, i);
	return (1);
}

void	more_exec_error(int err, char *msg)
{
	if (err == 4)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		perror(" ");
		g_exit_code = 1;
	}
	else if (err == 5)
		perror(msg);
	else if (err == 6)
		perror("here_doc error :");
	else if (err == 8)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": unclosed quotes\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}

void	exec_exit_error(int err, char *msg)
{
	char	*err_str;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err == 1)
	{
		err_str = strerror(errno);
		ft_putendl_fd(err_str, STDERR_FILENO);
		g_exit_code = errno;
	}
	else if (err == 2)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
		g_exit_code = 127;
	}
	else if (err == 3)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		g_exit_code = 126;
	}
	else if (err == 4 || err == 5 || err == 6 || err == 7 || err == 8)
		more_exec_error(err, msg);
	return ;
}
