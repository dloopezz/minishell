/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:51:58 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/16 18:34:04 by dlopez-s         ###   ########.fr       */
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
	else if (i == 3)
		ft_putstr_fd("OLDPWD is not set\n", STDERR_FILENO);
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

void	exec_exit_error(int err, char *msg, int errnum)
{
	if (err == 1)
		ft_putstr_fd("Invalid number of arguments\n", 2);
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error:");
	else if (err == 4)
		perror("no such file or directory :");
	else if (err == 5)
		msg = ft_strjoin(msg, ": no such file or directory");
	else if (err == 6)
		perror("command not found :");
	else if (err == 7)
		perror("here_doc error :");
	else if (err == 8)
		ft_putstr_fd("Command not found\n", 2);
	exit (errnum);
}
