/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:38:34 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/17 20:21:04 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// //!quitar pa entregar
// void read_list(t_token *cmd_lst)
// {
	// t_token	*aux_lst;
// 
	// aux_lst = cmd_lst;
	// while (aux_lst)
	// {
		// int i = 0;
		// printf("\n\033[33mNEW ARG: \033[0m\n");
		// while (aux_lst->args[i])
		// {
			// printf("ARG[i]: |%s|\n", aux_lst->args[i]);
			// para detectar espacios
			// int k = 0;
			// while (aux_lst->args[i][k])
			// {
				// if (aux_lst->args[i][k] == 32)
				// {
					// printf("\033[31mCHAR: SPACE \u26A0\033[0m\n");
					// k++;
				// }
				// else
					// printf("CHAR: %c\n", aux_lst->args[i][k++]);
			// }
			// i++;
		// }
		// printf("TYPE: %d\n", aux_lst->type);
		// aux_lst = aux_lst->next;	
	// }
	// printf("\n");
// }

//conts: 
// 0 - i
// 1 - j
// 2 - n
char	**split_cmd(t_token *tokens, char *cmd)
{
	int	conts[3];

	conts[0] = 0;
	conts[1] = 0;
	conts[2] = 0;
	tokens->args = ft_calloc(sizeof(char *), count_words(cmd, ' ') + 1);
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "utils_token.c", 59, tokens->args); //LEAKS
	while (cmd[conts[0]])
	{
		tokens->args[conts[2]] = ft_calloc(1, sizeof(char)
				* (ft_strlen(cmd) + 1));
		printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "utils_token.c", 63, tokens->args[conts[2]]); //LEAKS
		if (!tokens->args[conts[2]])
			exit(EXIT_FAILURE);
		if (cmd[conts[0]] == '\0')
			break ;
		if (cmd[conts[0]] == DQUOTES || cmd[conts[0]] == SQUOTES)
			conts[0] = select_mode(tokens, cmd, conts, QUOTED);
		else
			conts[0] = select_mode(tokens, cmd, conts, UNQUOTED);
		conts[2]++;
	}
	return (tokens->args);
}

t_token	*add_token(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;
	t_token	*aux;

	new = ft_calloc(1, sizeof(t_token));
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "utils_token.c", 84, new); //LEAKS
	new->args = split_cmd(new, cmd);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	set_redir(new);
	if (!cmd_lst)
		cmd_lst = new;
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

t_token	*add_tokenfront(t_token *cmd_lst, char *cmd, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "utils_token.c", 108, new); //LEAKS
	new->args = split_cmd(new, cmd);
	new->type = type;
	set_redir(new);
	if (!cmd_lst)
		cmd_lst = new;
	else
	{
		new->next = cmd_lst;
		new->prev = NULL;
		cmd_lst = new;
	}
	return (cmd_lst);
}
