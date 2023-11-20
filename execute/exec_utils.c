/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/17 17:03:06 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ft_strncmp(&line[0], ">", 1) == 0 && ft_strncmp(&line[1], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'", 1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0 && ft_strncmp(&line[2], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'", 1), 258);
		else if (ft_strncmp(&line[0], "<", 1) == 0 && ft_strncmp(&line[1], "<", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `<'", 1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0 || ft_strncmp(&line[0], "<", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `newline'", 1), 258);
	}
	return (1);
}