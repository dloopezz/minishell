/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/17 15:01:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_variable_string(char *variable)
{
	char	*tmp;

	tmp = ft_strjoin(variable, "=");
	if (!tmp)
		error_msg("failed tmp");
	return (tmp);
}

char	*remove_extra_spaces(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	result = malloc(strlen(str) + 1);
	if (!result)
		error_found("Memory allocation failed");
	while (str[i])
	{
		if (str[i] && str[i] != ' ')
			while (str[i] && str[i] != ' ')
				result[j++] = str[i++];
		else
		{
				result[j++] = str[i++];
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	result[j] = '\0';
	return (result);
}

//TODO revisar en un futuro que los free (var_name) no de fallos
char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_name;
	char	*var_fill;
	char	**new_env;
	char	*clean_string;

	new_env = malloc(sizeof(*env) * (ft_matrix_len(env) + 1));
	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		var_name = create_variable_string(variable);
		if (!env)
			return (NULL);
		clean_string = remove_extra_spaces(str);
		var_fill = ft_strjoin(var_name, clean_string);
		//free (clean_string);
		return (env = ft_new_env(pos + 1, -1, env, var_fill), env);
	}
	else
	{
		var_name = create_variable_string(variable);
		clean_string = remove_extra_spaces(str);
		env[pos] = ft_strjoin(var_name, clean_string);
        //free(clean_string);
		if (!env[pos])
			error_msg("failed malloc");
	}
	return (free(var_name), &env[pos]);
}

char	**setvar_cd(char *variable, char *str, char **env)
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
		var_name = create_variable_string(variable);
		if (!env)
			return (NULL);
		var_fill = ft_strjoin(var_name, str);
		env = ft_new_env(pos + 1, -1, env, var_fill);
		return (env);
	}
	else
	{
		var_name = create_variable_string(variable);
		env[pos] = ft_strjoin(var_name, str);
		if (!env[pos])
			error_msg("failed malloc");
	}
	return (free(var_name), &env[pos]);
}
