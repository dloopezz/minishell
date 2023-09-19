/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:25:38 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/19 18:31:24 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_found(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

/* void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
} */

int	ft_open(char *file, int check)
{
	int	fd;

	if (check == INFILE)
	{
		fd = open(file, O_RDONLY, 0644);
		if (access(file, R_OK) < 0)
			error_found("|failed to open file| ");
	}
	if (check == OUTFILE)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (access(file, W_OK | R_OK) < 0)
			error_found("|failed to open file| ");
	}
	if (fd < 0)
		error_found("|failed to open file| ");
	return (fd);
}
