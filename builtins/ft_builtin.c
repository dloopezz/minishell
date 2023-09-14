/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/14 12:50:49 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//# define FAILED_MALLOC			0b00000000000000000000001


int	ft_builtin(t_token *tokens, t_data *data)
{
	/* if (!tokens)
		return (0); */
	printf("USING BUILTINS\n");
	if (ft_strncmp(tokens->args[0], "cd\0", 3) == 0)
		return (ft_cd(tokens, data->envi));
	if (ft_strncmp(tokens->args[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(tokens->args[0], "echo\0", 5) == 0)
		return (ft_echo(tokens));
	if (ft_strncmp(tokens->args[0], "unset\0", 6) == 0)
		return (ft_unset(&tokens->args[0], data->envi));
	if (ft_strncmp(tokens->args[0], "export\0", 7) == 0)
		return (ft_export(tokens, data->envi));
	if (ft_strncmp(tokens->args[0], "exit\0", 5) == 0)
		return (ft_exit(tokens->args));
	if (ft_strncmp(tokens->args[0], "env\0", 4) == 0)
		return (ft_env(data, tokens));
	return (-1);
}
