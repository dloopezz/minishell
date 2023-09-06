/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/09/06 15:32:35 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*add_token(t_token *cmd_lst)
{
	t_token	*new;
	t_token	*aux;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	// new->type = token_type;
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

//TODO crear nodos con info, detectar GGT y LLT y ignorar espacios
int	ft_parsing(char *line)
{
	t_token	*cmd_lst;
	t_token	*aux_lst;
	char	*cmd;
	int		i;
	int		j;
	int		flag;

	cmd_lst = ft_calloc(1, sizeof(t_token));
	aux_lst = cmd_lst;
	
	flag = 0;
	i = -1;
	while (line[++i])
	{
		cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		while (line[i] == ' ') 
			i++;
		j = 0;
		while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
		{
			// printf("Line[i]: %c\n", line[i]);
			cmd[j++] = line[i++];
		}
		// while (line[i] == ' ') 
		// 	i++;
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>') && (line[i - 1] && line[i - 1] != '|' && line[i - 1] != '<' && line[i - 1] != '>') && flag == 0) 
			i--;

		if (line[i] == '|' || line[i] == '<' || line[i] == '>')  //lo mismo 2 veces: para operadores y cmds (optimizable)
		{
			flag = 0;
			j = 0;
			cmd[j++] = line[i++];
			cmd[j] = '\0';
			cmd_lst->data = cmd;
			//hacer get_type del ult caracter y crear token ya con esa info
			add_token(cmd_lst);
			printf("OP_NODE: %s\n", cmd_lst->data);
			cmd_lst = cmd_lst->next;
		}
		else
		{
			flag = 1;
			cmd[j]  = '\0';
			cmd_lst->data = cmd;
			add_token(cmd_lst);
			printf("CMD_NODE: %s\n", cmd_lst->data);
			cmd_lst = cmd_lst->next;
		}
	}
	//checkear que se haya creado la lista bien
	cmd_lst = aux_lst;
	while (cmd_lst->next)
	{
		printf("LST_DATA: %s\n", cmd_lst->data);
		cmd_lst = cmd_lst->next;	
	}
	return (0);
}
