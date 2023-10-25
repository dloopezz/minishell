/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/10/25 16:23:13 by dlopez-s         ###   ########.fr       */
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
		if (cmd[i] == DOUBLE_QUOTES || cmd[i] == SINGLE_QUOTES)
			i = select_mode(tokens, cmd, i, n, QUOTED);
		else
			i = select_mode(tokens, cmd, i, n, UNQUOTED);
		n++;
	}
	return (tokens->args);
}

t_token	*add_token(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	new->args = split_cmd(new, cmd);
	new->type = type;
	new->next = NULL;
	if (!cmd_lst)
		cmd_lst = new;
	else
	{
		aux = cmd_lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	return (cmd_lst);
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
	read_list(tokens);
	// free (cmd);
	return (tokens);
}
