/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/16 17:50:58 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_check_n(char *argv)
{
	int	i;

	i = 0;
	if (ft_strncmp(argv, "-n", 2) == 0)
	{
		while (argv[++i])
		{
			if (argv[i] != 'n' && argv[i] != ' ')
				return (1);
		}
		return (0);
	}
	i = -1;
	while (argv[++i])
	{
		if (argv[i] != 'n')
			return (1);
	}
	if (argv[0] == 'n')
		return (1);
	if (!argv[0])
		return (1);
	return (0);
}

int	ft_echo(t_token *token, int fd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!token->args[1])
	{
		ft_putstr_fd("\n", fd);
		return (0);
	}
	while (token->args[i] && ft_check_n(token->args[i]) == 0)
	{
		new_line = 0;
		i++;
	}
	while (token->args[i])
	{
		ft_putstr_fd(token->args[i], fd);
		if (token->args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (new_line == 1)
		ft_putstr_fd("\n", fd);
	return (0);
}
