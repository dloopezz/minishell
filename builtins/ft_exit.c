/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:29:14 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 17:54:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO revisar por que no funciona bien el isdigit
static bool	check_first_arg(char *argv)
{
	bool	sign;

	sign = true;
	if (*argv == '-')
	{
		sign = false;
		argv++;
	}
	else if (*argv == '+')
		argv++;
	if (ft_isdigit((int)argv) != 0)
	{
		printf("argv[1] %d\n", ft_atoi(argv));
		return (false);
	}
	if (ft_strlen(argv) == 19)
	{
		if ((sign && argv[ft_strlen(argv) - 1] > '8') \
			|| (!sign && argv[ft_strlen(argv) - 1] > '7'))
			return (false);
	}
	else if (ft_strlen(argv) > 19)
		return (false);
	return (true);
}

int	ft_exit(char **args)
{
	if (args)
		write(STDERR_FILENO, "exit\n", 5);
	//printf("el argumento es %s\n", args[1]);
	if (args[1])
	{
	//	printf("bool %d\n", check_first_arg(args[1]));
		if (!check_first_arg(args[1]))
		{
			//printf("argv[1] %s\n", args[1]);
	//		printf("funciona\n");
			error_arg_msg(args[1], 1);
		}
		else if (ft_strlen(args[1]) > 2)
			error_arg_msg(args[1], 2);
		else
		{
	//		printf("entra\n");	
			if (ft_strlen(args[1]) > 19)
				exit(ft_atol(*args));
		//return (false);
		}
	}
	exit(ft_atoi(args[1]));
	return (0);
}
