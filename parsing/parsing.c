/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/03 15:22:25 by dlopez-s         ###   ########.fr       */
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
		if (line[*i] == DOUBLE_QUOTES)
		{
			cmd[(*j)++] = line[(*i)++]; //copy first quotes
			while (line[*i] && line[*i] != DOUBLE_QUOTES)
				cmd[(*j)++] = line[(*i)++];
			if (line[*i] != DOUBLE_QUOTES)
				error_found("unclosed quotes :(");
			cmd[(*j)++] = line[(*i)++]; //copy last quotes
		}
		else if (line[*i] == SINGLE_QUOTES)
		{
			cmd[(*j)++] = line[(*i)++]; //copy first quotes
			while (line[*i] && line[*i] != SINGLE_QUOTES)
				cmd[(*j)++] = line[(*i)++];
			if (line[*i] != SINGLE_QUOTES)
				error_found("unclosed quotes :(");
			cmd[(*j)++] = line[(*i)++]; //copy last quotes
		}
		else
		{
			printf("LINE[i]: |%c|\n", line[*i]);
			if (line[*i] == '$' && line[*i + 1] && (line[*i + 1] == DOUBLE_QUOTES || line[*i + 1] == SINGLE_QUOTES))
			{
				printf("entra\n");
				(*i)++;
			}
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
		tokens = add_file_token(tokens, &i, line);
		if (!line[i])
			break;
	}
	read_list(tokens);
	// free (cmd);
	return (tokens);
}
