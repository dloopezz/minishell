/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/18 16:11:58 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_op(t_token *tokens)
{
	t_token	*aux_lst;
	int i = 0;

	aux_lst = tokens;
	while (aux_lst)
	{
		while (aux_lst->args[i])
		{
			if (aux_lst->type != CMD)
				return (1);
			i++;
		}
		aux_lst = aux_lst->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	int i;
	t_data	*data ;
	t_token	*tokens;
	(void) argc;
	(void) argv;

	tokens = NULL;
	line = "";		//inicializacion a lo guarro
	data = ft_calloc(1, sizeof(t_data));
	data->envi = envp;
	data->env_copy = ft_calloc(ft_matrix_len(envp) + 1, sizeof(char *));
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (line == NULL)
			break ;
		i = -1;
		while (envp[++i])
			data->env_copy[i] = ft_strdup(envp[i]);
		tokens = ft_parsing(line, tokens);
		if (!ft_strchr(line, '|') && !ft_strchr(line, '>') && !ft_strchr(line, '<'))
		{
				if (ft_builtin(tokens, data) == -1)
					ft_execute(tokens, data);
		}
		else
			ft_execute(tokens, data);
		// free(tokens);
		// printf("Line: %s\n", line);
	}
	return (0);
}



//? si no hay | en la linea de comandos entra en builtins.
//? si hay | entra en pipex.
//? si en pipex hay un comando de builtins, busca el comando y ejecuta por los builtins.
//TODO tener en cuenta funcion opendir para executer.