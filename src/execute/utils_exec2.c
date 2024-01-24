/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:23:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/19 14:25:41 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	builtin(char *cmd, t_token *tokens, t_data *data, int fd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(fd), 1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(tokens, data->envi), 1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data, tokens, fd), 1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(tokens, data, fd), 1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(tokens, data), 1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(tokens, fd), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		status = ft_exit(tokens->args);
	g_exit_code = status;
	return (0);
}

void	signal_wait(pid_t pid)
{
	int		status;

	sig_child();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
}
