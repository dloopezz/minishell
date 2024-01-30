/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:33:47 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/30 14:51:37 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	copy_until_quote(t_token *tokens, char *cmd, int *conts, int quote_type)
{
	(void)quote_type;
	conts[0]++;
	while (cmd[conts[0]] && cmd[conts[0]] != SQUOTES
		&& cmd[conts[0]] != DQUOTES)
		tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
	conts[0]++;
}

int	quoted_mode(t_token *tokens, char *cmd, int *conts, int quote_type)
{
	conts[1] = 0;
	while (cmd[conts[0]] && cmd[conts[0]] != quote_type)
		tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
	conts[0]++;
	while (cmd[conts[0]] && (cmd[conts[0]] != ' ' || cmd[conts[0]] == SQUOTES
			|| cmd[conts[0]] == DQUOTES))
	{
		if (cmd[conts[0]] == SQUOTES)
			copy_until_quote(tokens, cmd, conts, quote_type);
		else if (cmd[conts[0]] == DQUOTES)
			copy_until_quote(tokens, cmd, conts, quote_type);
		else if (cmd[conts[0]] != ' ')
		{
			while (cmd[conts[0]] && cmd[conts[0]] != ' '
				&& cmd[conts[0]] != SQUOTES && cmd[conts[0]] != DQUOTES)
				tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
		}
	}
	tokens->args[conts[2]][conts[1]] = '\0';
	return (conts[0]);
}

int	unquoted_mode(t_token *tokens, char *cmd, int *conts)
{
	conts[1] = 0;
	while (cmd[conts[0]] && cmd[conts[0]] != ' ')
	{
		if (cmd[conts[0]] && cmd[conts[0]] == DQUOTES)
		{
			conts[0]++;
			while (cmd[conts[0]] && cmd[conts[0]] != DQUOTES)
				tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
			conts[0]++;
		}
		else if (cmd[conts[0]] && cmd[conts[0]] == SQUOTES)
		{
			conts[0]++;
			while (cmd[conts[0]] && cmd[conts[0]] != SQUOTES)
				tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
			conts[0]++;
		}
		else
			tokens->args[conts[2]][conts[1]++] = cmd[conts[0]++];
	}
	tokens->args[conts[2]][conts[1]] = '\0';
	return (conts[0]);
}

int	select_mode(t_token *tokens, char *cmd, int *conts, int mode)
{
	int	quote_type;

	if (mode == QUOTED)
	{
		quote_type = cmd[conts[0]];
		skip_spaces(cmd, &conts[0]);
		conts[0]++;
		conts[0] = quoted_mode(tokens, cmd, conts, quote_type);
		skip_spaces(cmd, &conts[0]);
	}
	else if (mode == UNQUOTED)
	{
		skip_spaces(cmd, &conts[0]);
		conts[0] = unquoted_mode(tokens, cmd, conts);
		skip_spaces(cmd, &conts[0]);
	}
	return (conts[0]);
}
