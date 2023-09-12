/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:19:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 15:57:16 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **pepe)
{
	char *line;
	(void) argc;
	//printf("%d\n", julian);
	(void) argv;
	line = "a";		//inicializacion a lo guarro
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (ft_parsing(line, pepe) == 1)
			return (0);
		// printf("Line: %s\n", line);
	}
	return (0);
}
