/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/17 19:47:58 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_file(char *file, int type)
{
	int	fd_ret;

	if (type == 0)
		fd_ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ret == -1)
	{
		ft_putstr_fd("no such file...\n", 2);
		return (-1);
	}
	return (fd_ret);
}

void	check_slash(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strncmp(&line[i], "\\", 1) == 0)
			error_arg_msg("Syntax error near unexpected token '\\'", 1);
}

int	check_some_syntax(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_strncmp(&line[0], ">", 1) == 0
			&& ft_strncmp(&line[1], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'",
					1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0
			&& ft_strncmp(&line[2], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'",
					1), 258);
		else if (ft_strncmp(&line[0], "<", 1) == 0
			&& ft_strncmp(&line[1], "<", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `<'",
					1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0
			|| ft_strncmp(&line[0], "<", 1) == 0)
			return (error_syntax_msg
				("Syntax error near unexpected token `newline'", 1), 258);
	}
	return (1);
}
