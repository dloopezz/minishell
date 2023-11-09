/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:38:34 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/08 13:08:19 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//!quitar pa entregar
void read_list(t_token *cmd_lst)
{
	t_token	*aux_lst;

	aux_lst = cmd_lst;
	while (aux_lst)
	{
		int i = 0;
		printf("\n\033[33mNEW ARG: \033[0m\n");
		while (aux_lst->args[i])
		{
			printf("ARG[i]: |%s|\n", aux_lst->args[i]);
			//para detectar espacios
			// int k = 0;
			// while (aux_lst->args[i][k])
			// {
			// 	if (aux_lst->args[i][k] == 32)
			// 	{
			// 		printf("\033[31mCHAR: SPACE \u26A0\033[0m\n");
			// 		k++;
			// 	}
			// 	else
			// 		printf("CHAR: %c\n", aux_lst->args[i][k++]);
			// }
			i++;
		}
		printf("TYPE: %d\n", aux_lst->type);
		aux_lst = aux_lst->next;	
	}
	printf("\n");
}

t_token *get_last_node(t_token *tokens)
{
	t_token	*aux_lst;

	aux_lst = tokens;
	while (aux_lst->next)
		aux_lst = aux_lst->next;
	return (aux_lst);
}

//ADD FILE AS INDEPENDENT TOKEN
t_token *add_file_token(t_token *tokens, int *i, char *line)
{	
	t_token *aux;
	t_token *last_node;
	char *filename;
	
	aux = tokens;
	last_node = get_last_node(aux);
	int k;
	if (is_redir(last_node->type))
	{
		filename = ft_calloc(1, (sizeof(char) * ft_strlen(line)) + 1);
		k = 0;
		(*i)++;
		skip_spaces(line, i);
		while (line[*i] && line[*i] != ' ')
			filename[k++] = line[(*i)++];
		filename[k] = '\0';
		tokens = add_token(tokens, filename, FILE);
	}
	return (tokens);
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
		if (cmd[i] == DQUOTES || cmd[i] == SQUOTES)
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
	new->prev = NULL;
	if (!cmd_lst)
	{
		cmd_lst = new;
	}
	else
	{
		aux = cmd_lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
		new->prev = aux;
	}
	return (cmd_lst);
}