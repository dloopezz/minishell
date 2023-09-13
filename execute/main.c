/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 15:43:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_data	*data;
	t_token	*tokens;
	(void) argc;
	(void) argv;

	tokens = NULL;
	line = "a";		//inicializacion a lo guarro
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		tokens = ft_parsing(line, tokens);
			
		data = ft_calloc(1, sizeof(t_data));
		data->envi = envp;
		ft_builtin(tokens, data);
		// free(tokens);
		// printf("Line: %s\n", line);
	}
	return (0);
}
