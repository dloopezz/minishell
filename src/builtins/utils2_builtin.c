/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/20 18:54:02 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

char	*process_existing_variable(char *variable, char *str)
{
	char	*var_name;
	char	*clean_string;
	char	*var_fill;

	var_name = create_variable_string(variable);
	clean_string = remove_extra_spaces(str);
	var_fill = ft_strjoin(var_name, clean_string);
	free(var_name);
	free(clean_string);
	if (!var_fill)
		error_msg("failed malloc");
	return (var_fill);
}

char	*process_unexisting_variable(char *variable, char *str)
{
	char	*var_name;
	char	*clean_string;
	char	*var_fill;

	var_name = create_variable_string(variable);
	clean_string = remove_extra_spaces(str);
	var_fill = ft_strjoin(var_name, clean_string);
	free(clean_string);
	if (!var_fill)
		error_msg("failed malloc");
	return (var_fill);
}

char	*set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_fill = NULL;

	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		var_fill = process_unexisting_variable(variable, str);
		if (!env)
			return (NULL);
		env = ft_new_env(pos + 1, -1, env, var_fill);
		return (var_fill);
	}
	else
	{
		var_fill = process_existing_variable(variable, str);
		env[pos] = var_fill;
		return (var_fill);
	}
}

char	**setvar_cd(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_name;
	char	*var_fill;

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
