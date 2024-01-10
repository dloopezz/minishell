/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:28 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/09 16:53:31 by crtorres         ###   ########.fr       */
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
	////printf(MAGENTA"direccion str es %p en utils2_builtin.c en línea: 66 y es %s\n"RESET, str, str);
	clean_string = remove_extra_spaces(str);
	////printf(MAGENTA"direccion clean es %p en utils2_builtin.c en línea: 66 y es %s\n"RESET, clean_string, clean_string);
	var_fill = ft_strjoin(var_name, clean_string);
	//printf(RED"direccion %p en utils2_builtin.c en línea: 66 y es %s\n"RESET, var_fill, var_fill);
	if (!var_fill)
		error_msg("failed malloc");
	free(var_name);
	free(clean_string);
	return (var_fill);
}
//! el free quita el leak pero crea un fallo al hacer cd -
char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_fill;
	char	*var;

	var_fill = NULL;
	pos = get_posvar_in_env(variable, env);
	var_fill = process_existing_variable(variable, str);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		if (!env)
			return (NULL);
		env = ft_new_env(pos + 1, env, var_fill);
		return (env);
	}
	else
	{
		/*
			OLDPWD = "string literl"
			PWD = strdup("");
		*/
		var = var_fill;
		//free (var_fill);
		//free (env[pos]);
		env[pos] = var;
		//printf(CYAN"str es %s en utils2_builtin.c en linea 93\n", str);
		//printf(CYAN"direccion de var_fill es %p en utils2_builtin.c en linea 93\n", var_fill);
		//printf(CYAN"direccion es %p en utils2_builtin.c en linea 93\n", env[pos]);
		return (&env[pos]);
	}
}

//TODO revisar en un futuro que los free (var_name) no de fallos
/* char	**set_var_in_env(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_name;
	char	*var_fill;
	// char	**new_env;
	char	*clean_string;

	// new_env = malloc(sizeof(*env) * (ft_matrix_len(env) + 1));
	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		var_name = create_variable_string(variable, str);
		if (!env)
			return (NULL);
		clean_string = remove_extra_spaces(str);
		var_fill = ft_strjoin(var_name, clean_string);
		free (clean_string);
		env = ft_new_env(pos + 1, env, var_fill);
		return (env);
	}
	else
	{
		var_name = create_variable_string(variable, str);
		clean_string = remove_extra_spaces(str);
		env[pos] = ft_strjoin(var_name, clean_string);
		free(clean_string);
		if (!env[pos])
			error_msg("failed malloc");
	}
	return (free(var_name), &env[pos]);
} */

/* char	**setvar_cd(char *variable, char *str, char **env)
{
	int		pos;
	char	*var_name;
	char	*var_fill;

	pos = get_posvar_in_env(variable, env);
	if (pos < 0)
	{
		pos = ft_matrix_len(env);
		var_name = create_variable_string(variable, str);
		if (!env)
			return (NULL);
		var_fill = ft_strjoin(var_name, str);
		env = ft_new_env(pos + 1, env, var_fill);
		return (env);
	}
	else
	{
		var_name = create_variable_string(variable, str);
		env[pos] = ft_strjoin(var_name, str);
		//printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "utils2_builtin.c", 171, env[pos]);
		if (!env[pos])
			error_msg("failed malloc");
	}
	return (free(var_name), &env[pos]);
} */
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
		(*env)[pos] = ft_strjoin(var_name, str);
		//printf(CYAN"direccion de var_fill es %p en ft_cd.c en linea 92\n", var_fill);
		//printf(CYAN"direccion es %p en ft_cd.c en linea 92\n", env[pos]);
	}
	return (free (var_name), &(*env)[pos]);
}