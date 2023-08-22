/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:19:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/08/22 17:17:07 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main()
{
	char *line;
	
	line = "a";
	while (line != NULL)
	{
		// ft_parsing();
		line = readline("minishell > ");
	}
	return (0);
}
