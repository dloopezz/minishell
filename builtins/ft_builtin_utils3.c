/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/02 14:32:50 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_variable_string(char *variable, char *str)
{
	char	*tmp;

	if (!str)
		tmp = ft_strjoin(variable, NULL);
	else
		tmp = ft_strjoin(variable, "=");
	if (!tmp)
		error_msg("failed tmp");
	return (tmp);
}

//TODO revisar en un futuro que los free (var_name) no de fallos
char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_name;
	char	*var_fill;
	char	**new_env;

	new_env = malloc(sizeof(*env) * (ft_matrix_len(env) + 1));
	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		var_name = create_variable_string(variable, str);
		if (!env)
			return (NULL);
		var_fill = ft_strjoin(var_name, str);
		env = ft_new_env(pos + 1, -1, env, var_fill);
		return (env);
	}
	else
	{
		var_name = create_variable_string(variable, str);
		env[pos] = ft_strjoin(var_name, str);
		if (!env[pos])
			error_msg("failed malloc");
	}
	return (free(var_name), &env[pos]);
}
