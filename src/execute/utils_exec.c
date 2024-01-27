/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/27 15:35:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_file(char *file, int type)
{
	int	fd_ret;
	
	if (strlen(file) > sizeof(file))
        return (-1);
	if (type == 0)
		fd_ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ret == -1)
	{
		perror("error opening file\n");
		g_exit_code = 1;
		exit(EXIT_FAILURE);
	}
	return (fd_ret);
}

int	check_slash(char *token)
{
	char	*pos;

	pos = ft_strstr(token, "\\");
	if (pos != NULL)
		return (error_syntax_msg("Syntax error near unexpected token '\\'",
				1), 258);
	return (0);
}

int	syntax_nl(t_token *token)
{
	if (token->type == LT && !token->next)
		return (error_syntax_msg("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == GT && !token->next)
		return (error_syntax_msg("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == GGT && !token->next)
		return (error_syntax_msg("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == LLT && !token->next)
		return (error_syntax_msg("Syntax error near unexpected token `newline'",
				1), 258);
	return (0);
}

int	syntax_no_pipe(t_token *token)
{
	if (token->type == LT && token->next->type == 1)
		return (error_syntax_msg("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GT && token->next->type == 1)
		return (error_syntax_msg("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == LLT && token->next->type == 1)
		return (error_syntax_msg("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GGT && token->next->type == 1)
		return (error_syntax_msg("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == PIPE && !token->next)
		return (error_syntax_msg("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == PIPE && token->next->type == PIPE)
		return (error_syntax_msg("Syntax error near unexpected token `||'",
				1), 258);
	return (0);
}

int	check_some_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (syntax_nl(tmp) != 0)
			return (g_exit_code = 258, 258);
		else if (syntax_no_pipe(tmp) != 0)
			return (g_exit_code = 258, 258);
		else if (check_slash(*tmp->args) != 0)
			return (g_exit_code = 258, 258);
		tmp = tmp->next;
	}
	return (0);
}
