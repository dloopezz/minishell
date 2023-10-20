/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/10/20 12:02:49 by dlopez-s         ###   ########.fr       */
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

// int count_char(char *line, char c)
// {
// 	int i;
// 	int n;

// 	n = 0;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == c)
// 			n++;		
// 		i++;
// 	}
// 	return (n);
// }

// void	check_quotes(char *line)
// {
// 	int		s_quotes;
// 	int		d_quotes;

// 	s_quotes = count_char(line, SINGLE_QUOTES);
// 	d_quotes = count_char(line, DOUBLE_QUOTES);
// 	// printf("SINGLE: %d\nDOUBLE: %d\n", s_quotes, d_quotes);
// 	if ((s_quotes % 2) != 0 || (d_quotes % 2) != 0)
// 	{
// 		printf("\n> tengo que gestionar esto :(\n");
// 	}
// }


// void single_quotes(char *line, char *cmd, int i, int j)
// {
	
// }

void double_quotes(char *line, char *cmd, int i, int j)
{
	if (line[i] == DOUBLE_QUOTES || line[i] == SINGLE_QUOTES)
	{
		i++;
		while (line[i] != DOUBLE_QUOTES && line[i] != SINGLE_QUOTES)
			cmd[j++] = line[i++];
		i++;
	}
	else
		cmd[j++] = line[i++];
}

void quotes_mode(char *line, char *cmd, int i, int j)
{
	// single_quotes(line, cmd, i, j);
	double_quotes(line, cmd, i, j);
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

	// check_quotes(line);
	while (line[++i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		while (line[i] == ' ' && line[i])
			i++;
		j = 0;
		// printf("LINE[i]: %c\n", line[i]);
		while (line[i] && !is_operator(line[i]))
		{
			cmd[j++] = line[i++];
			// while (line[i] == ' ')
			// {
			// 	if (line[i + 1] != ' ' && !is_operator(line[i + 1]))
			// 		cmd[j++] = line[i];
			// 	i++;
			// }

			////quotes
			// if (line[i] == DOUBLE_QUOTES || line[i] == SINGLE_QUOTES)
			// {
			// 	i++;
			// 	while (line[i] != DOUBLE_QUOTES && line[i] != SINGLE_QUOTES)
			// 		cmd[j++] = line[i++];
			// 	i++;
			// }
			// else
			// 	cmd[j++] = line[i++];
			// quotes_mode(cmd, line, i, j);	
		}
		if (is_operator(line[i]) && line[i - 1] && !is_operator(line[i - 1]) && flag == 0)
			i--;
		if (is_operator(line[i]))
		{
			flag = 0;
			j = 0;
			if (line[i] &&  line[i + 1] && line[i] != '|' && line[i + 1] == line[i])
				cmd[j++] = line[i++];
			cmd[j++] = line[i];
		}
		else
			flag = 1;
		type = select_type(line, i);
		cmd[j] = '\0';
		tokens = add_token(tokens, cmd, type);
		//para que no pete
		if (!line[i])
			break;
	}
	// free (cmd);
	read_list(tokens);
	return (tokens);
}
