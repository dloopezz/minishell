/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/28 12:13:44 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_slash(char *token)
{
	char	*pos;

	pos = ft_strstr(token, "\\");
	if (pos != NULL)
		return (err_syntax("Syntax error near unexpected token '\\'",
				1), 258);
	return (0);
}

int	syntax_nl(t_token *token)
{
	if (token->type == LT && !token->next)
		return (err_syntax("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == GT && !token->next)
		return (err_syntax("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == GGT && !token->next)
		return (err_syntax("Syntax error near unexpected token `newline'",
				1), 258);
	else if (token->type == LLT && !token->next)
		return (err_syntax("Syntax error near unexpected token `newline'",
				1), 258);
	return (0);
}

int	syntax_no_pipe(t_token *token)
{
	if (token->type == LT && token->next->type == 1)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GT && token->next->type == 1)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == LLT && token->next->type == 1)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GGT && token->next->type == 1)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == PIPE && !token->next)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == PIPE && token->next->type == PIPE)
		return (err_syntax("Syntax error near unexpected token `||'",
				1), 258);
	return (0);
}

bool	ft_check_space_case(char *line)
{
	bool	character;
	bool	especial;

	character = false;
	especial = false;
	while (*line)
	{
		if (*line != ' ')
			character = true;
		if (*line == '<' || *line == '>')
			especial = true;
		else if (*line == '|')
		{
			if (especial)
				return (err_syntax("Syntax error near unexpected token `|'",
						1), true);
			especial = true;
		}
		else if (*line != ' ')
			especial = false;
		line++;
	}
	if (character == true && especial == true)
		return (err_syntax("Syntax error near unexpected token `>'",
				1), character && especial);
	else
		return (character && especial);
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
