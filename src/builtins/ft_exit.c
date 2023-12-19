/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:29:14 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/19 16:45:50 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//TODO revisar por que no funciona bien el isdigit
static bool	check_first_arg(char *argv)
{
	bool	sign;
	int		i;

	i = 0;
	sign = true;
	if (argv[i] == '-')
	{
		sign = false;
		argv++;
	}
	else if (argv[i] == '+')
		i++;
	if (ft_isdigit(argv[i]) == 0)
		return (false);
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
	if (args[1])
	{
		if (!check_first_arg(args[1]))
			error_arg_msg(args[1], 1);
		else if (ft_matrix_len(args) > 2)
		{
			error_arg_msg(args[1], 2);
			return (0);
		}
		else
		{
			if (ft_strlen(args[1]) > 19)
			{
				g_exit_code = (ft_atol(args[1]) % 256);
				exit(ft_atol(args[1]));
			}
			g_exit_code = (ft_atoi(args[1]) % 256);
		}
	}
	return (exit(g_exit_code), g_exit_code);
}
