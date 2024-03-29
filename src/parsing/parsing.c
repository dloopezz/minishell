/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/02/01 11:50:09 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	copy_with_quotes(char *line, char *cmd, int *conts, int quote_type)
{
	cmd[(conts[1])++] = line[(conts[0])++];
	while (line[conts[0]] && line[conts[0]] != quote_type)
		cmd[(conts[1])++] = line[(conts[0])++];
	if (line[conts[0]] != quote_type)
	{
		exec_exit_error(8, "");
		return (UNCLOSED);
	}
	cmd[(conts[1])++] = line[(conts[0])++];
	return (CLOSED);
}

int	copy_line(char *line, char *cmd, int *conts)
{
	int	quotes;

	quotes = 0;
	while (line[conts[0]] && !is_operator(line[conts[0]]))
	{
		if (line[conts[0]] == DQUOTES)
			quotes = copy_with_quotes(line, cmd, conts, DQUOTES);
		else if (line[conts[0]] == SQUOTES)
			quotes = copy_with_quotes(line, cmd, conts, SQUOTES);
		else
		{
			if (line[conts[0]] == '$' && line[conts[0] + 1]
				&& (line[conts[0] + 1] == DQUOTES
					|| line[conts[0] + 1] == SQUOTES))
				(conts[0])++;
			else
				cmd[(conts[1])++] = line[(conts[0])++];
		}
	}
	return (quotes);
}

void	close_cmd(char *line, char *cmd, int *conts, int *flag)
{
	if (line[conts[0]] && (conts[0]) != 0 && is_operator(line[conts[0]])
		&& !is_operator(line[conts[0] - 1]) && *flag == 0)
		(conts[0])--;
	if (is_operator(line[conts[0]]))
	{
		*flag = 0;
		conts[1] = 0;
		if (line[conts[0]] && line[conts[0] + 1] && line[conts[0]] != '|'
			&& line[conts[0] + 1] == line[conts[0]])
			cmd[(conts[1])++] = line[(conts[0])++];
		cmd[(conts[1])++] = line[conts[0]];
	}
	else
		*flag = 1;
	cmd[conts[1]] = '\0';
}

//conts
//0 - i
//1 - j
t_token	*ft_parsing(char *line, t_data *data, t_token *tokens)
{
	int		conts[2];

	conts[0] = -1;
	while (line[++conts[0]])
	{
		data->cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		skip_spaces(data->cmd, &conts[0]);
		conts[1] = 0;
		data->is_quoted = copy_line(line, data->cmd, conts);
		if (data->is_quoted == UNCLOSED)
		{
			if (!add_token(tokens, data->cmd, data->tk_type, data->is_quoted))
				return (NULL);
			return (free(data->cmd), tokens);
		}
		close_cmd(line, data->cmd, conts, &data->op_flag);
		data->tk_type = select_type(line, conts[0]);
		tokens = add_token(tokens, data->cmd, data->tk_type, data->is_quoted);
		if (tokens == NULL)
			return (free (data->cmd), NULL);
		if (!line[conts[0]])
			break ;
		free(data->cmd);
	}
	return (re_parse(&tokens, data->cmd), tokens);
}
