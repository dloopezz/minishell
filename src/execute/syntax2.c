/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:56:23 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/29 16:56:38 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_slash(char *token)
{
	char	*pos;

	pos = ft_strstr(token, "\\");
	if (pos != NULL)
		return (err_syntax("Syntax error near unexpected token '\\'",
				1), 258);
	return (0);
}
