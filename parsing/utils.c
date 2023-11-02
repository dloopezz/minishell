/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:00:26 by lopezz            #+#    #+#             */
/*   Updated: 2023/11/02 13:23:39 by dlopez-s         ###   ########.fr       */
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

bool is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool is_redir(int type)
{
	if (type == LT || type == LLT || type == GT || type == GGT)
		return (true);
	return (false);
}

void skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
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
