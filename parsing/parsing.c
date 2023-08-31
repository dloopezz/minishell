/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:16:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/08/31 17:18:43 by dlopez-s         ###   ########.fr       */
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

int	ft_parsing(char *line)
{
	t_token	*cmd_lst;
	t_token	*aux_lst;
	char	*cmd;
	int		i;
	int		j;

	cmd = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
	cmd_lst = ft_calloc(1, sizeof(t_token));
	aux_lst = cmd_lst;
	
	if (ft_strncmp(line, "exit", 4) == 0)
		return (1);
	
	i = -1;
	while (line[++i])
	{
		while (line[i] == ' ') 
			i++;
		j = 0;
		while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
		{
			printf("Line[i]: %c\n", line[i]);
			cmd[j++] = line[i++];
			
		}
		// while (line[i] == ' ') 
		// 	i++;
		printf("2Line[i]: %c\n", line[i]);
		// if ((line[i] == '|' || line[i] == '<' || line[i] == '>') && (line[i - 1] && line[i - 1] != '|' && line[i - 1] != '<' && line[i - 1] != '>')) 
		// {
		// 	printf("entra\n");
		// 	i--;
		// }

		//error en esta linea (culpa de i++):
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')  //lo mismo 2 veces: para operadores y cmds (optimizable)
		{
			j = 0;
			cmd[j++] = line[i++];
			cmd[j] = '\0';
			cmd_lst->data = cmd;
			//hacer get_type del ult caracter y crear token ya con esa info
			add_token(cmd_lst);
			printf("CMD: %s\n", cmd);
			printf("CMD_LST: %s\n", cmd_lst->data);
			cmd_lst = cmd_lst->next;
		}
		else
		{			
			cmd[j]  = '\0';
			cmd_lst->data = cmd;
			add_token(cmd_lst);
			printf("CMD: %s\n", cmd);
			printf("CMD_LST: %s\n", cmd_lst->data);
			cmd_lst = cmd_lst->next;
		}
	}
	//checkear que se haya creado la lista bien (ahora solo pilla el ult token)
	cmd_lst = aux_lst;
	while (cmd_lst->next)
	{
		// printf("LST_DATA: %s\n", cmd_lst->data);
		cmd_lst = cmd_lst->next;	
	}
	return (0);
}

// int	ft_parsing(char *line)
// {
// 	int		i;
// 	int		j;
// 	// int	token_type;
// 	char	*cmd = ft_calloc(1, sizeof(char) * ft_strlen(line));
// 	t_token	*cmd_lst;
// 	t_token	*aux_lst;

// 	if (ft_strncmp(line, "exit", 4) == 0)
// 		return (1);

// 	cmd_lst = ft_calloc(1, sizeof(t_token));
// 	aux_lst = cmd_lst;
	
// 	i = -1;
// 	while (line[++i])
// 	{
// 		while (line[i] == ' ') //poner tb \t y eso 
// 			i++;
	
// 		// cmd_lst->type = select_type(line, i);
// 		// if (cmd_lst->type == 3 || cmd_lst->type == 5)  //para que no pille segundo > como uno solo
// 		// 	i++;

// 		j = 0;	
// 		while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
// 		{
// 			// printf("LINE: %c\n", line[i]);
// 			cmd[j++] = line[i++];
// 			// printf("CMD: %c\n", cmd[j]);
// 		}
// 		// printf("CMD: %s\n", cmd);
		
// 		add_token(cmd_lst, line);
// 		// printf("Char: %c is type %d. List Content: %c\n", line[i], cmd_lst->type, cmd_lst->data);
// 		cmd_lst = cmd_lst->next;
// 	}
// 	return (0);
// }


