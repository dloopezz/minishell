/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/06 17:25:42 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"+

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
	int i;
	int	new_line;

	i = 0;
	new_line = 0;
	if (!argv[0])
	{
		printf("\n");
		return (0);
	}
	while (ft_check_n(argv[i]) == 0)
	{
		new_line = 1;
		i++;
	}
	while (argv[0])
	{
		printf("%s", argv[0]);
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