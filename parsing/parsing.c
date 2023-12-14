/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/13 15:59:15 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void copy_line(char *line, char *cmd, int *i, int *j)
{
	while (line[*i] && !is_operator(line[*i]))
	{
		if (line[*i] == DQUOTES)
		{
			cmd[(*j)++] = line[(*i)++]; //copy first quotes
			while (line[*i] && line[*i] != DQUOTES)
				cmd[(*j)++] = line[(*i)++];
			if (line[*i] != DQUOTES)
				error_found("unclosed quotes :(");
			cmd[(*j)++] = line[(*i)++]; //copy last quotes
		}
		else if (line[*i] == SQUOTES)
		{
			cmd[(*j)++] = line[(*i)++]; //copy first quotes
			while (line[*i] && line[*i] != SQUOTES)
				cmd[(*j)++] = line[(*i)++];
			if (line[*i] != SQUOTES)
				error_found("unclosed quotes :(");
			cmd[(*j)++] = line[(*i)++]; //copy last quotes
		}
		else
		{
			if (line[*i] == '$' && line[*i + 1] && (line[*i + 1] == DQUOTES || line[*i + 1] == SQUOTES))
				(*i)++;
			else
				cmd[(*j)++] = line[(*i)++];
		}
	}
}

void	close_cmd(char *line, char *cmd, int *i, int *j, int *flag)
{
	if (line[*i] && (*i) != 0 && is_operator(line[*i]) && !is_operator(line[*i - 1]) && *flag == 0)
		(*i)--;
	if (is_operator(line[*i]))
	{
		*flag = 0;
		*j = 0;
		if (line[*i] && line[*i + 1] && line[*i] != '|' && line[*i + 1] == line[*i])
			cmd[(*j)++] = line[(*i)++];
		cmd[(*j)++] = line[*i];
	}
	else
		*flag = 1;
	cmd[*j] = '\0';
}

t_token	*re_type(t_token *token, int type_find, int new_type, int prev_type)
{
	t_token	*cur = token;
	
	while (cur)
	{
		if (cur->prev && cur->type == type_find && cur->prev->type == prev_type)
			cur->type = new_type;
		cur = cur->next;
	}
	return (token);
}

t_token	*ft_parsing(char *line, t_token *tokens)
{
	char	*cmd;
	int		i;
	int		j;
	int		flag;
	int		type;

	tokens = NULL;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		skip_spaces(cmd, &i);
		j = 0;
		copy_line(line, cmd, &i, &j);
		close_cmd(line, cmd, &i, &j, &flag);
		type = select_type(line, i);
		tokens = add_token(tokens, cmd, type);
		if (!line[i])
			break;
	}
    tokens = re_type(tokens, CMD, DELM, LLT);
    tokens = re_type(tokens, CMD, INFILE, LT);
    tokens = re_type(tokens, CMD, OUTFILE, GT);
    tokens = re_type(tokens, CMD, OUTFILE, GGT);
	reorder_tokens(&tokens);
	return (free (cmd), tokens);
}
