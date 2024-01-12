/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/12 11:44:36 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*create_variable_string(char *variable, char *str)
{
	char	*tmp;

	if (!str)
		tmp = ft_strjoin(variable, NULL);
	else
		tmp = ft_strjoin(variable, "=");
	//printf(RED"direccion %p en utils2_builtin.c en línea: 19 y es %s\n"RESET, tmp, tmp);
	if (!tmp)
		error_msg("failed tmp\n");
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
		error_found("Memory allocation failed\n");
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

char	*process_existing_variable(char *variable, char *str)
{
	char	*var_name;
	char	*clean_string;
	char	*var_fill;

	var_name = create_variable_string(variable, str);
	clean_string = remove_extra_spaces(str);
	var_fill = ft_strjoin(var_name, clean_string);
	if (!var_fill)
		error_msg("failed malloc");
	free(var_name);
	free(clean_string);
	return (var_fill);
}

char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_fill;
	// char	*var;

	var_fill = NULL;
	pos = get_posvar_in_env(variable, env);
	var_fill = process_existing_variable(variable, str);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		if (!env)
			return env;
		env = ft_new_env(pos + 1, env, var_fill);
		return env;
	}
	else
	{
		// if (ft_strlen(env[pos]) != ft_strlen(var_fill))
		// {
			free(env[pos]);
			env[pos] = NULL;
		// }
		env[pos] = var_fill;
		return env;
	}
}

char	**setvar_in_cd(char *variable, char *str, char ***env)
{
	int		pos;
	char	*var_fill = NULL;
	char	*var_name;

	pos = get_posvar_in_env(variable, *env);
	//var_fill = process_existing_variable(variable, str);
	if (pos < 0)
	{
		pos = ft_matrix_len(*env);
		if (!env)
			return (NULL);
		var_name = create_variable_string(variable, str);
		var_fill = ft_strjoin(var_name, str);
		*env = ft_new_env(pos + 1, *env, var_fill);
		return (*env);
	}
	else
	{
		var_name = create_variable_string(variable, str);
		// if (ft_strcmp(variable, "OLDPWD") == 0 && ft_strlen((*env)[pos]) != (ft_strlen(var_name) + ft_strlen(str)))
		// {
		// 	printf("ENTRAAA\n\n");
			free((*env)[pos]);
		// }
		// printf("ENVPOS: %p\n", (*env)[pos]);
		(*env)[pos] = ft_strjoin(var_name, str);
	}
	return (free (var_name), (*env));
}
