/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/19 20:14:10 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	select_type(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<')
	{
		if (i != 0 && line[i - 1] == '<')
			return (LLT);
		else
			return (LT);
	}
	else if (line[i] == '>')
	{
		if (i != 0 && line[i - 1] == '>')
			return (GGT);
		else
			return (GT);
	}
	else
		return (CMD);
}

void	copy_with_quotes(char *line, char *cmd, int *conts, int quote_type)
{
	cmd[(conts[1])++] = line[(conts[0])++];
	while (line[conts[0]] && line[conts[0]] != quote_type)
		cmd[(conts[1])++] = line[(conts[0])++];
	if (line[conts[0]] != quote_type)
		error_found("unclosed quotes :(");
	cmd[(conts[1])++] = line[(conts[0])++];
}

void	copy_line(char *line, char *cmd, int *conts)
{
	while (line[conts[0]] && !is_operator(line[conts[0]]))
	{
		if (line[conts[0]] == DQUOTES)
			copy_with_quotes(line, cmd, conts, DQUOTES);
		else if (line[conts[0]] == SQUOTES)
			copy_with_quotes(line, cmd, conts, SQUOTES);
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
t_token	*ft_parsing(char *line, t_token *tokens)
{
	char	*cmd;
	int		conts[2];
	int		flag;
	int		type;

	tokens = NULL;
	flag = 0;
	conts[0] = -1;
	while (line[++conts[0]])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "cmd.c", 101, cmd); //LEAKS
		skip_spaces(cmd, &conts[0]);
		conts[1] = 0;
		copy_line(line, cmd, conts);
		close_cmd(line, cmd, conts, &flag);
		type = select_type(line, conts[0]);
		tokens = add_token(tokens, cmd, type);
		if (!line[conts[0]])
			break ;
		free(cmd);
	}
	tokens = re_type_all(tokens);
	reorder_tokens(&tokens);
	// read_list(tokens);
	return (free(cmd), tokens);
}
