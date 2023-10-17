/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/16 12:52:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_n(char *argv)
{
	int	i;

	if (ft_strncmp(argv, "-n", 2))
		return (1);
	argv += 2;
	while (*argv && *argv == 'n')
		argv++;
	i = 0;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (1);
	}
	return (0);
}

int	ft_echo(t_token *token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!token->args[1])
	{
		printf("\n");
		return (0);
	}
	while (ft_check_n(token->args[i]) == 0)
	{
		new_line = 0;
		i++;
	}
	while (token->args[i])
	{
		printf("%s", token->args[i]);
		if (token->args[i + 1])
			printf(" ");
	i++;
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}
