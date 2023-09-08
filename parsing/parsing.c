/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/09/08 15:04:36 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	select_type(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (LLT);
		else
			return (LT);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (GGT);
		else
			return (GT);
	}
	else
		return (CMD);
}

//TODO ignorar espacios y detectar GGT y LLT
int	ft_parsing(char *line)
{
	t_token	*cmd_lst;
	char	*cmd;
	int		i;
	int		j;
	int		flag;
	int		type;

	cmd_lst = NULL;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		while (line[i] == ' ')
			i++;
		j = 0;
		while (line[i] && !is_operator(line[i]))
		{
			cmd[j++] = line[i++];
			while (line[i] == ' ')
			{
				if (line[i + 1] != ' ' && !is_operator(line[i + 1]))
					cmd[j++] = line[i];
				i++;
			}
		}
		if (is_operator(line[i]) && line[i - 1] && !is_operator(line[i - 1]) && flag == 0)
			i--;

		if (is_operator(line[i]))
		{
			flag = 0;
			j = 0;
			cmd[j++] = line[i];
		}
		else
			flag = 1;
		type = select_type(line, i);
		cmd[j]  = '\0';
		cmd_lst = add_token(cmd_lst, cmd, type);
	}
	read_list(cmd_lst);
	return (0);
}
