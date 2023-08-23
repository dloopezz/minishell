/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:19:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/08/23 13:05:41 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main()
{
	char *line;
	
	line = "a";		//inicializar a lo guarro
	while (line != NULL)
	{
		line = readline("\u263B > ");
		if (ft_parsing(line) == 1)
			return (0);
		printf("Line: %s\n", line);
	}
	return (0);
}
