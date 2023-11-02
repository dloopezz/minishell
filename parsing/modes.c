/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:33:47 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/02 13:20:37 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	after_quotes(t_token *tokens, char *cmd, int i, int n, int quote_type)
// {
// 	while (cmd[i] && (cmd[i] != ' ' || cmd[i] == SINGLE_QUOTES || cmd[i] == DOUBLE_QUOTES))
// 	{
// 		if (cmd[i] == SINGLE_QUOTES)
// 		{
// 			i++;
// 			while (cmd[i] && cmd[i] != SINGLE_QUOTES)
// 				tokens->args[n][j++] = cmd[i++];
// 			i++;
// 		}
// 		else if (cmd[i] == DOUBLE_QUOTES)
// 		{
// 			i++;
// 			while (cmd[i] && cmd[i] != DOUBLE_QUOTES)
// 				tokens->args[n][j++] = cmd[i++];
// 			i++;
// 		}
// 		else if (cmd[i] != ' ')
// 		{
// 			while (cmd[i] && cmd[i] != ' ' && cmd[i] != SINGLE_QUOTES && cmd[i] != DOUBLE_QUOTES)
// 				tokens->args[n][j++] = cmd[i++];
// 		}
// 	}
// }

int	quoted_mode(t_token *tokens, char *cmd, int i, int n, int quote_type)
{
	int	j;

	j = 0;
	while (cmd[i] != quote_type)
		tokens->args[n][j++] = cmd[i++];
	i++; //skip quote
	while (cmd[i] && (cmd[i] != ' ' || cmd[i] == SINGLE_QUOTES || cmd[i] == DOUBLE_QUOTES))
	{
		if (cmd[i] == SINGLE_QUOTES)
		{
			i++;
			while (cmd[i] && cmd[i] != SINGLE_QUOTES)
				tokens->args[n][j++] = cmd[i++];
			i++;
		}
		else if (cmd[i] == DOUBLE_QUOTES)
		{
			i++;
			while (cmd[i] && cmd[i] != DOUBLE_QUOTES)
				tokens->args[n][j++] = cmd[i++];
			i++;
		}
		else if (cmd[i] != ' ')
		{
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != SINGLE_QUOTES && cmd[i] != DOUBLE_QUOTES)
				tokens->args[n][j++] = cmd[i++];
		}
	}
	tokens->args[n][j] = '\0';
	return (i);
}

int	unquoted_mode(t_token *tokens, char *cmd, int i, int n)
{
	int j;

	j = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] && cmd[i] == DOUBLE_QUOTES)
		{
			i++;
			while (cmd[i] && cmd[i] != DOUBLE_QUOTES)
				tokens->args[n][j++] = cmd[i++];
			i++;
		}
		else if (cmd[i] && cmd[i] == SINGLE_QUOTES)
		{
			i++;
			while (cmd[i] && cmd[i] != SINGLE_QUOTES)
				tokens->args[n][j++] = cmd[i++];
			i++;
		}
		else
			tokens->args[n][j++] = cmd[i++];
	}
	tokens->args[n][j] = '\0';
	return (i);
}

int	select_mode(t_token *tokens, char *cmd, int i, int n, int mode)
{
	if (mode == QUOTED)
	{
		skip_spaces(cmd, &i);
		i =	quoted_mode(tokens, cmd, i + 1, n, cmd[i]); //cmd[i] is quote_type, i + 1 to skip quote
		skip_spaces(cmd, &i);
	}
	else if (mode == UNQUOTED)
	{
		skip_spaces(cmd, &i);
		i = unquoted_mode(tokens, cmd, i, n);
		skip_spaces(cmd, &i);
	}
	return (i);
}