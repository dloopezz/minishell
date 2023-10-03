/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:00:26 by lopezz            #+#    #+#             */
/*   Updated: 2023/10/02 17:21:03 by crtorres         ###   ########.fr       */
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
			printf("ARG[i]: %s\n", aux_lst->args[i]);
			// //para detectar espacios
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

t_token	*add_token(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	if (ft_strchr(cmd, '"') == 0)
	{
		printf("entra\n");
		new->args = ft_split(cmd, ' ');
	}
	new->args = ft_split(cmd, ' ');
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
/* char	*ft_quote(char *str)
{
	int		i;
	int		r;
	int		quote;
	char	*new;
	char	*ret;

	i = 0;
	r = 0;
	new = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		while (str[i] && str[i] == SQUOTE || str[i] == DQUOTE)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (ft_strchr("\t\v\n >|<", str[i]))
					str[i] = -str[i];
				new[r++] = str[i++];
			}
			i++;
		}
		if (!str[i])
			break;
		new[r++] = str[i++];
	}
	new[r] = 0;
	ret = ft_strdup(new);
	free_all(2, 0, & new, & str);
	return (ret);
} */
/* int 	check_close_quotes(char *cmd)
{
	char 	c;
	int		quotes;
	int		i;
	
	quotes = 0;
	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{	
		while (cmd[i] && (cmd[i] != '"' || cmd[i] != '\''))
			i++;
		if (cmd[i] && (cmd[i] == '"' || cmd[i] == '\''))
		{
			c = cmd[i];
			if (cmd[i++] == c)
				quotes = cmd[i];
			while (cmd[i] && cmd[i] != c)
				i++;
			if (cmd[i++] == c)
			quotes++;
			else 
				break;
		}
	}
	if (quotes % 2)
	{
		error_msg("unclosed quotes");
		free (cmd);
	}
	return (0);
} */

bool is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
