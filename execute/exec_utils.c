/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/05 16:26:18 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

void	check_slash(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strncmp(&line[i], "\\", 1) == 0)
			error_arg_msg("Syntax error near unexpected token '\\'", 1);		
}

void	check_infile(t_token *token, int fd_inf)
{
	printf("token->type es %d\n", token->type);
	printf("token infile es %s\n", *token->args);
	if (token->type == LT)
	{
		fd_inf = open_file(*token->next->args, 0);
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
	else if (token->type == LLT)
	{
		fd_inf = open_file(*token->next->args, 0);
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
	else if (fd_inf != STDIN_FILENO)
	{
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
}

void	check_outfile(t_token *token, int fd_outf)
{
	printf("token outfile es %s\n", *token->args);
	if (token->type == GT)
	{
		fd_outf = open_file(*token->next->args, 1);
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);	
	}
	else if (token->type == GGT)
	{
		fd_outf = open_file(*token->next->args, 2);
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);	
	}
	else if (fd_outf != STDOUT_FILENO)
	{
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);
	}
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