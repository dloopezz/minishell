/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 14:45:01 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_n(char *argv)
{
	if (ft_strncmp(argv, "-n", 2))
		return (1);
	printf("argv es %s\n", argv);
	argv += 2;
	while (*argv && *argv == 'n')
		argv++;
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

/* int	main(int argc, char **argv, char **envp)
{
	ft_echo(argv);
	return (0);
} */