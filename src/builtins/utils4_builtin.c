/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:14:27 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/19 19:14:45 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*substring_before_last_slash(const char *path)
{
	size_t	last_slash;
	char	*new_str;

	last_slash = ft_strlen(path) - 1;
	while (last_slash > 0 && path[last_slash] != '/')
		last_slash--;
	if (last_slash == 0)
		return ("");
	new_str = malloc(sizeof(char) * last_slash + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, path, last_slash);
	new_str[last_slash] = '\0';
	return (new_str);
}
