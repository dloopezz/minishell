/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/11 17:23:02 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(t_token *token)
{
	if ((ft_strncmp(token->args[0], "cd\0", 3) == 0)
		|| (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		|| (ft_strncmp(token->args[0], "env\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "export\0", 7) == 0)
		|| (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		|| (ft_strncmp(token->args[0], "exit\0", 5) == 0))
		return (0);
	else
		return (1);
}

int	ft_builtin(t_token *tokens, t_data *data)
{
	if (ft_strncmp(tokens->args[0], "cd\0", 3) == 0)
		return (ft_cd(tokens, data->envi));
	if (ft_strncmp(tokens->args[0], "pwd\0", 4) == 0)
		return (ft_pwd(4));
	if (ft_strncmp(tokens->args[0], "echo\0", 5) == 0)
		return (ft_echo(tokens));
	if (ft_strncmp(tokens->args[0], "env\0", 4) == 0)
		return (ft_env(data, tokens));
	if (ft_strncmp(tokens->args[0], "export\0", 7) == 0)
		return (ft_export(tokens, data));
	if (ft_strncmp(tokens->args[0], "unset\0", 6) == 0)
		return (ft_unset(tokens, data));
	if (ft_strncmp(tokens->args[0], "exit\0", 5) == 0)
		return (ft_exit(tokens->args));
	return (-1);
}
