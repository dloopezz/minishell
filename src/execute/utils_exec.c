/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:23:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/30 15:17:38 by crtorres         ###   ########.fr       */
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
	{
		if (search_var_in_env("PATH", data->envi) == NULL)
			return (exec_exit_error(2, tokens->args[0]), 0);
		else
			return (ft_cd(tokens, data->envi), 1);
	}
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

int	get_pipes(t_token *tokens)
{
	t_token	*aux;
	int		n_pipes;

	aux = tokens;
	n_pipes = 0;
	while (aux->next)
	{
		if (aux->type == PIPE)
			n_pipes++;
		aux = aux->next;
	}
	return (n_pipes);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	return (pid);
}
