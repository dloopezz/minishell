/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 11:19:21 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//# define FAILED_MALLOC			0b00000000000000000000001


static int	builtin_export(char *str, char ***env)
{
	int		success;
	char	**tab;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 6, ' ');
		if (!tab)
			error_msg("failed malloc");
		success = ft_export(*tab, env);
		ft_free_arrows(tab, -1);
	}
	return (success);
}

int	ft_builtin(t_token *token, t_data *data)
{
	/* if (!token)
		return (0); */
	if (ft_strncmp(token->args[0], "cd\0", 3) == 0)
		return (ft_cd(token, data->envi));
	if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		return (ft_echo(token->args));
	if (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		return (ft_unset(&token->args[0], data->envi));
	if (ft_strncmp(token->args[0], "export\0", 7) == 0)
		return (builtin_export(token->args[0], &data->envi));
	if (ft_strncmp(token->args[0], "exit\0", 5) == 0)
		return (ft_exit(token->args));
	return (-1);
}
