/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:48:49 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/12 12:16:54 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(char *cmd, t_token *tokens, t_data *data, int fd)
{
	printf("entra\n");
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(fd), 1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return(ft_cd(tokens, data->envi), 1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data, tokens), 1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(tokens, data), 1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(tokens, data), 1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(tokens), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(tokens->args), 1);
	return (0);
}
