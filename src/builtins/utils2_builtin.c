/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/30 13:11:46 by dlopez-s         ###   ########.fr       */
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
	if (!tmp)
		error_arg_msg("failed tmp", 4);
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
		error_arg_msg("Memory allocation failed", 4);
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
		error_arg_msg("failed malloc", 4);
	free(var_name);
	free(clean_string);
	return (var_fill);
}

char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_fill;

	var_fill = NULL;
	pos = get_posvar_in_env(variable, env);
	var_fill = process_existing_variable(variable, str);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		if (!env)
			return (env);
		env = ft_new_env(env, var_fill);
		return (env);
	}
	else
	{
		free(env[pos]);
		env[pos] = NULL;
		env[pos] = var_fill;
		return (env);
	}
}

/* char	**setvar_in_cd(char *variable, char *str, char ***env)
{
	int		pos;
	char	*var_fill;
	char	*var_name;

	var_fill = NULL;
	pos = get_posvar_in_env(variable, *env);
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
		free((*env)[pos]);
		(*env)[pos] = ft_strjoin(var_name, str);
	}
	return (free (var_name), (*env));
} */
