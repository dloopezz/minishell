/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:11:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/15 12:51:21 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_pwd(int fd)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (EXIT_FAILURE);
	ft_putendl_fd(path, fd);
	return (EXIT_SUCCESS);
}
