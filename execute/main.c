/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:19:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/08 15:39:42 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main()
{
	char *line;
	
	line = "a";		//inicializacion a lo guarro
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (ft_parsing(line) == 1)
			return (0);
		// printf("Line: %s\n", line);
	}
	return (0);
}
