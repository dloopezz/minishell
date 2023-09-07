/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/09/07 18:21:38 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*add_token(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	new->data = cmd;
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

//TODO detectar GGT y LLT y ignorar espacios
int	ft_parsing(char *line)
{
	t_token	*cmd_lst;
	t_token	*aux_lst;
	char	*cmd;
	int		i;
	int		j;
	int		flag;
	int		type;

	cmd_lst = NULL;
	flag = 0;
	i = -1;
	// 
	while (line[++i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		while (line[i] == ' ')
			i++;
		j = 0;
		while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
		{
			// printf("Line[i]: %d\n", line[i]);
			cmd[j++] = line[i++];
			while (line[i] == ' ')
			{
				i++;				
			}
		}
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>') && (line[i - 1] && line[i - 1] != '|' && line[i - 1] != '<' && line[i - 1] != '>') && flag == 0) 
			i--;

		if (line[i] == '|' || line[i] == '<' || line[i] == '>')  //lo mismo 2 veces: para operadores y cmds (optimizable)
		{
			flag = 0;
			j = 0;
			type = select_type(line, i);
			cmd[j++] = line[i];
			cmd[j] = '\0';
			cmd_lst = add_token(cmd_lst, cmd, type);
		}
		else
		{
			flag = 1;
			type = select_type(line, i);
			cmd[j]  = '\0';
			cmd_lst = add_token(cmd_lst, cmd, type);
		}
	}
	
	//checkear que se haya creado la lista bien
	aux_lst = cmd_lst;
	while (aux_lst)
	{
		printf("\nLST_DATA: %s\n", aux_lst->data);
		int k = 0;
		while (aux_lst->data[k])
		{
			printf("CHAR: %d\n", aux_lst->data[k]);
			k++;
		}
		// printf("LST_TYPE: %d\n", aux_lst->type);
		aux_lst = aux_lst->next;	
	}

	return (0);
}
