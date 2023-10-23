/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/10/23 14:45:22 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	select_type(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<')
	{
		if (line[i - 1] == '<')
			return (LLT);
		else
			return (LT);
	}
	else if (line[i] == '>')
	{
		if (line[i - 1] == '>')
			return (GGT);
		else
			return (GT);
	}
	else
		return (CMD);
}

int count_char(char *line, char c)
{
	int i;
	int n;

	n = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			n++;		
		i++;
	}
	return (n);
}

void	check_quotes(char *line)
{
	int		s_quotes;
	int		d_quotes;

	s_quotes = count_char(line, SINGLE_QUOTES);
	d_quotes = count_char(line, DOUBLE_QUOTES);
	// printf("SINGLE: %d\nDOUBLE: %d\n", s_quotes, d_quotes);
	if ((s_quotes % 2) != 0 || (d_quotes % 2) != 0)
	{
		printf("\n> tengo que gestionar esto :(\n");
	}
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
	i = 0;

	check_quotes(line);
	while (line[i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		while (line[i] == ' ')
			i++;
		j = 0;
		while (line[i] && !is_operator(line[i]))
		{
			cmd[j++] = line[i++];
			// printf("LINE[i]: %c\n", line[i]);
			if (line[i] == DOUBLE_QUOTES)
			{
				i++;
				while (line[i] != DOUBLE_QUOTES)
				{
					printf("LINE[i]: %c\n", line[i]);
					cmd[j++] = line[i++];
				}
				i++;
			}
			//else
			// // ignore spaces
			// while (line[i] == ' ')
			// {
			// 	if (line[i + 1] != ' ' && !is_operator(line[i + 1]))
			// 		cmd[j++] = line[i];
			// 	i++; 
			// }
		}
		if (is_operator(line[i]) && line[i - 1] && !is_operator(line[i - 1]) && flag == 0)
			i--;
		if (is_operator(line[i]))
		{
			flag = 0;
			j = 0;
			if (line[i] != '|' && line[i + 1] == line[i])
				cmd[j++] = line[i++];
			cmd[j++] = line[i++];
		}
		else
			flag = 1;
		//printf("LINE[i]: %c\n", line[i]);
		type = select_type(line, i);
		i = -1;
		//! borrar este while antes del merge e introducir en la parte de Dani para no gestionar '\'
		while (line[++i])
		{
			if (ft_strncmp(&line[i], "\\", 1) == 0)
				error_arg_msg("Syntax error near unexpected token '\\'", 1);
		}	
		cmd[j] = '\0';
		printf("%s\n", cmd);
		tokens = add_token(tokens, cmd, type);
	}
	free (cmd);
	read_list(tokens);
	return (tokens);
}
