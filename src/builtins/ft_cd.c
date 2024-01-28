/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/28 10:49:13 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//? +2 para '/' y '\0'
char	*build_relative_path(const char *base_path, char *relative_path)
{
	size_t	base_len;
	size_t	relative_len;
	char	*result;

	if (!base_path || !relative_path)
		return (NULL);
	base_len = ft_strlen(base_path);
	relative_len = ft_strlen(relative_path);
	if (base_len == 0 || relative_len == 0)
		return (NULL);
	result = malloc(base_len + relative_len + 2);
	if (!result)
		return (exec_exit_error(1, ""), NULL);
	ft_strcpy(result, base_path);
	if (result[base_len - 1] != '/')
		ft_strcat(result, "/");
	ft_strcat(result, relative_path);
	return (result);
}

int	change_directory_loop(char *cur_path)
{
	if (chdir(cur_path) == -1)
	{
		return (-1);
	}
	return (0);
}

int	change_directory(char *path, char *old_path, int i)
{
	char	*cur_path;

	if (i == 0)
	{
		cur_path = ft_strdup(path + 7);
		if (change_directory_loop(cur_path) == -1)
			return (free(path), -1);
		free (cur_path);
	}
	if (is_absolute_path(path) && i == 1)
		cur_path = path;
	else
	{
		cur_path = build_relative_path(old_path, path);
		if (!cur_path)
			return (err_cd_msg("", 3), -1);
		free (cur_path);
	}
	if (i == 1 && chdir(cur_path) == -1)
		return (check_and_free_path(cur_path));
	return (0);
}
//!	else if (i == 1)
//!		free (cur_path);
//! free(cur_path);

int	handle_special_cases(char **env, char **old, char **current, t_token *token)
{
	char	*home;
	char	*actual_path;

	home = get_home(env);
	actual_path = NULL;
	if (!token->args[1] || !ft_strncmp(token->args[1], "--", 2))
	{
		if (chdir(home) == -1)
			return (free_cd(*old, *current, 1), -1);
		free (*current);
		*current = ft_strdup(home);
	}
	else if (!ft_strncmp(token->args[1], "-", 1))
	{
		actual_path = search_var_in_env("OLDPWD", env);
		change_directory(actual_path, *old, 0);
		ft_pwd(1);
	}
	else if (change_directory(token->args[1], *old, 1) == -1)
		return (free_cd(*old, *current, 2), -1);
	return (0);
}

int	ft_cd(t_token *token, char **env)
{
	char	*cur_path;
	char	*path_aux;
	char	*tmp;
	char	*old_path;
	int		result;

	old_path = getcwd(NULL, PATH_MAX);
	if (token->args[1] && ft_strncmp(token->args[1], "..", 2) == 0)
	{
		if (token->next && token->next->type == PIPE)
			return (0);
		cur_path = substring_before_last_slash(old_path);
	}
	else
	{
		path_aux = ft_strjoin(old_path, "/");
		cur_path = ft_strjoin(path_aux, token->args[1]);
		if (token->args[1])
			free(path_aux);
	}
	result = handle_special_cases(env, &old_path, &cur_path, token);
	if (result != 0)
		return (result);
	return (tmp = ft_pwd_cd(), set_var_in_env("OLDPWD", old_path, env),
		set_var_in_env("PWD", tmp, env), free_cd(old_path, cur_path, 2), 0);
}
