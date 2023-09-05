/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/05 16:48:17 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"+

int	ft_check_n(char *argvs)
{
	if (ft_strncmp(argvs, "-n", 2))
		return (0);
	argvs += 2;
	while (*argvs && *argvs == 'n')
		argvs++;
	return (1);
}

int	ft_echo(char **argvs)
{
	int i;
	int	new_line;

	i = 0;
	new_line = 0;
	if (!argvs[0])
	{
		printf("\n");
		return (0);
	}
	while (ft_check_n(argvs[i]) == 0)
	{
		new_line = 1;
		i++;
	}
	while (argvs[0])
	{
		printf("%s", argvs[0]);
		if (argvs[i + 1])
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