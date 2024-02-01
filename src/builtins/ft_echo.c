/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:01:34 by crtorres          #+#    #+#             */
/*   Updated: 2024/02/01 14:48:59 by crtorres         ###   ########.fr       */
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

int	ft_check_dollar(char *argv)
{
	if (ft_strncmp(argv, "$?", 2) == 0)
		return (g_exit_code);
	return (-1);
}

int	ft_check_n_dollar(char *argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strncmp(&argv[i], "$?", 2) == 0)
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
<
void	process_args(t_token *token, int fd, int *i)
{
	int	count_n_dollar;
	int	j;

	while (token->args[*i])
	{
		count_n_dollar = ft_check_n_dollar(token->args[*i]);
		if (count_n_dollar > 0)
		{
			j = 0;
			while (j < count_n_dollar)
			{
				ft_putnbr_fd(g_exit_code, fd);
				j++;
			}
			ft_putstr_fd(token->args[*i] + 2 * count_n_dollar, fd);
		}
		else if (ft_check_dollar(token->args[*i]) != -1)
			ft_putnbr_fd(g_exit_code, fd);
		else
			ft_putstr_fd(token->args[*i], fd);
		if (token->args[*i + 1])
			ft_putstr_fd(" ", fd);
		(*i)++;
	}
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
	process_args(token, fd, &i);
	if (new_line == 1)
		ft_putstr_fd("\n", fd);
	g_exit_code = 0;
	return (0);
}
