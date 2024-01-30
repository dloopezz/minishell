/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/30 12:52:35 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (token->type == LT && token->next->type == PIPE)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GT && token->next->type == PIPE)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == LLT && token->next->type == PIPE)
		return (err_syntax("Syntax error near unexpected token `|'",
				1), 258);
	else if (token->type == GGT && token->next->type == PIPE)
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
