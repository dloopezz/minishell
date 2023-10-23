/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/10/23 14:44:47 by dlopez-s         ###   ########.fr       */
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

int	quote_mode(t_token *tokens, char *cmd, int i, int n, int quote_type)
{
	int	j;
	int start;
	
	start = i;
	//aqui puede petar por acceder a null
	while (cmd[i] && cmd[i] != quote_type)
	{
		if (!cmd[i])
			error_found("unclosed quotes :(");
		i++;
	}
	//+1 to skip quote
	i = start + 1;
	j = 0;
	
	printf("cmd (after): %s\n", cmd);
	
	while (cmd[i] != quote_type)
		tokens->args[n][j++] = cmd[i++];
	tokens->args[n][j] = '\0';
	//+1 to skip quote
	return (i + 1);
}

char **split_cmd(t_token *tokens, char *cmd)
{
	int	i;
	int	j;
	int	n;
	
	i = 0;
	n = 0;
	//! muy feo lo del 100,  algo tipo count words
	tokens->args = ft_calloc(1, sizeof(char *) * (100));
	while (cmd[i])
	{		
		tokens->args[n] = ft_calloc(1, sizeof(char) * (ft_strlen(cmd) + 1));
		if (!tokens->args[n])
			exit(EXIT_FAILURE);
		j = 0;
		if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
		{
			i =	quote_mode(tokens, cmd, i, n, cmd[i]); //cmd[i] sera quote_type
			tokens->args[++n] = ft_calloc(1, sizeof(char) * (ft_strlen(cmd) + 1));
		}
		i = skip_spaces(cmd, i);
		while (cmd[i] && cmd[i] != ' ')
			tokens->args[n][j++] = cmd[i++];
		tokens->args[n++][j] = '\0';
		i = skip_spaces(cmd, i);
	}
	return (tokens->args);
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
		while (line[i] == ' ' && line[i])
			i++;
		j = 0;
		while (line[i] && !is_operator(line[i]))
		{
			if (line[i] == DOUBLE_QUOTES)
			{
				cmd[j++] = line[i++]; //copy first quotes
				while (line[i] && line[i] != DOUBLE_QUOTES)
					cmd[j++] = line[i++];
				if (line[i] != DOUBLE_QUOTES)
					error_found("unclosed quotes :(");
				cmd[j++] = line[i++]; //copy last quotes
			}
			else
				cmd[j++] = line[i++];
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
		i = -1;
		//! borrar este while antes del merge e introducir en la parte de Dani para no gestionar '\'
		while (line[++i])
		{
			if (ft_strncmp(&line[i], "\\", 1) == 0)
				error_arg_msg("Syntax error near unexpected token '\\'", 1);
		}	
		cmd[j] = '\0';
		printf("cmd (before): %s\n", cmd);
		tokens = add_token(tokens, cmd, type);
		if (!line[i])
			break;
	}
	// free (cmd);
	read_list(tokens);
	return (tokens);
}
