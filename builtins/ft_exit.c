/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:29:14 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/08 12:44:07 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!ft_isdigit(argv))
		return (false);
	if (ft_strlen(argv) == 19)
	{
		if ((sign && argv[ft_strlen(argv) - 1] > '8') \
			|| (!sign && argv[ft_strlen(argv) - 1] > '7'))
			return (false);
	}
	else if (ft_strlen(argv) > 19)
		return (false);
}

int	ft_exit(char *token, char **argv)
{
	if (token)
		write(STDERR_FILENO, "exit\n", 5);
	if (argv[1])
	{
		if (!check_first_arg(argv[1]))
			error_arg_msg(argv[1], 1);
		else if (ft_strlen(argv > 2))
			error_arg_msg(argv[1], 2);
		else
			exit(ft_atol(argv));
	}
	exit(0);
	return (0);
}
