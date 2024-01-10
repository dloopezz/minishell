/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:14:27 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/10 12:31:15 by crtorres         ###   ########.fr       */
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
	printf(ORANGE"direccion es %p en utils4_builtins.c en linea 26\n", new_str);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, path, last_slash);
	printf(ORANGE"direccion es %p en utils4_builtins.c en linea 29\n", new_str);
	new_str[last_slash] = '\0';
	return (new_str);
}

char	*get_home(char **env)
{
	char	*home_path;
	char	*return_path;

	home_path = search_var_in_env("HOME", env);
	if (!home_path)
		return (NULL);
	return_path = (home_path + 5);
	printf(ORANGE"direccion es %p en utils4_builtins.c en linea 41\n"RESET, return_path);
	printf(ORANGE"direccion es %p en utils4_builtins.c en linea 41\n"RESET, home_path);
	return (return_path);
}
