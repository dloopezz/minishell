/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 13:07:50 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_n(char *argv)
{
	if (ft_strncmp(argv, "-n", 2))
		return (0);
	argv += 2;
	while (*argv && *argv == 'n')
		argv++;
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 1;
	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	while (ft_check_n(argv[i]) == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[1])
	{
		printf("%s", argv[1]);
		if (argv[i + 1])
			printf(" ");
	i++;
	}
	if (new_line != 1)
		printf("\n");
	return (0);
}

/* int	main(int argc, char **argv, char **envp)
{
	ft_echo(argv);
	return (0);
} */