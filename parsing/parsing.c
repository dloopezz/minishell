/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/10/24 17:39:30 by crtorres         ###   ########.fr       */
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

int	quoted_mode(t_token *tokens, char *cmd, int i, int n, int quote_type)
{
	int	j;

	j = 0;
	while (cmd[i] != quote_type)
		tokens->args[n][j++] = cmd[i++];
	tokens->args[n][j] = '\0';
	//+1 to skip quote
	return (i + 1);
}
size_t	count_words(const char	*str, char c)
{
	size_t	countw;
	size_t	i;

	countw = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != c && str[i] != 0)
		{
			countw++;
			while (str[i] != c && str[i] != 0)
				i++;
		}
		else if (str[i] != 0)
			i++;
	}
	return (countw);
}

int	unquoted_mode(t_token *tokens, char *cmd, int i, int n)
{
	int j;

	j = 0;
	while (cmd[i] && cmd[i] != ' ')										//sacar bucle -> unquoted_mode	
	{
		if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
		{
			i++;
			while (cmd[i] != DOUBLE_QUOTES && cmd[i] != SINGLE_QUOTES)
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
		printf("entra\n");
		i = skip_spaces(cmd, i);
		i =	quoted_mode(tokens, cmd, i + 1, n, cmd[i]);  //cmd[i] is quote_type, i + 1 to skip quote
		if (cmd[i] == '\0')
			return (0);
/* 		if (cmd[i] == ' ')
			i++; */
		i = skip_spaces(cmd, i);
	}
	else if (mode == UNQUOTED)
	{
		printf("entra2\n");
		printf("cmd[i] es |%c|\n", cmd[i]);
		i = skip_spaces(cmd, i);
		i = unquoted_mode(tokens, cmd, i, n);
		//i = skip_spaces(cmd, i);
		//printf("entra\n");
	}
	return (i);
}


char **split_cmd(t_token *tokens, char *cmd)
{
	int	i;
	int	n;
	
	i = 0;
	n = 0;
	tokens->args = ft_calloc(sizeof(char *), count_words(cmd, ' ') + 1);
	while (cmd[i])
	{
		tokens->args[n] = ft_calloc(1, sizeof(char) * (ft_strlen(cmd) + 1));
		if (!tokens->args[n])
			exit(EXIT_FAILURE);
		if (cmd[i] == '\0')
			break ;
		/* if (cmd[i] == ' ')
			i++; */
		if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
		{
			printf("cmd[i] es |%c|\n", cmd[i]);
			i = select_mode(tokens, cmd, i, n, QUOTED);
			// if (i == 0)
			// 	break;
		}
		else
			i = select_mode(tokens, cmd, i, n, UNQUOTED);
		n++;
	}
	printf("esto es %s|%d|\n", tokens->args[n -1], i);
	return (tokens->args);
}
 
/* char **split_cmd(t_token *tokens, char *cmd)
{
	int	i;
	int	j;
	int	n;
	
	i = 0;
	n = 0;
	tokens->args = ft_calloc(sizeof(char *), count_words(cmd, ' ') + 1);
	while (cmd[i])
	{
		tokens->args[n] = ft_calloc(1, sizeof(char) * (ft_strlen(cmd) + 1));
		if (!tokens->args[n])
			exit(EXIT_FAILURE);
		// if (cmd[i] == '\0')
		// 	break ;
		j = 0;
		printf("cmd[i] es |%c|\n", cmd[i]);
		if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
		{
			printf("Entra\n");
			i =	quoted_mode(tokens, cmd, i + 1, n, cmd[i]);  //cmd[i] is quote_type, i + 1 to skip quote
			if (cmd[i] == '\0')
				break ;
			// tokens->args[n] = ft_calloc(1, sizeof(char) * (ft_strlen(cmd) + 1));
		}
		i = skip_spaces(cmd, i);
		//printf("cmd[i - 1] es %c\n", cmd[i ]);
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
			{
				printf("Entra2\n");
				i++;
				while (cmd[i] != DOUBLE_QUOTES && cmd[i] != SINGLE_QUOTES)
					tokens->args[n][j++] = cmd[i++];
				i++;
			}
			else
				tokens->args[n][j++] = cmd[i++];
		}
		tokens->args[n++][j] = '\0';
		//i = skip_spaces(cmd, i);
	}
	return (tokens->args);
} */

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
		if (ft_strncmp(&line[i], "\\", 1) == 0)
			error_arg_msg("Syntax error near unexpected token '\\'", 1);
	}
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
			else if (line[i] == SINGLE_QUOTES)
			{
				cmd[j++] = line[i++]; //copy first quotes
				while (line[i] && line[i] != SINGLE_QUOTES)
					cmd[j++] = line[i++];
				if (line[i] != SINGLE_QUOTES)
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
		cmd[j] = '\0';
		tokens = add_token(tokens, cmd, type);
		if (!line[i])
			break;
	}
	// free (cmd);
	//read_list(tokens);
	return (tokens);
}
