/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/10 12:17:49 by crtorres         ###   ########.fr       */
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
	//printf(ORANGE"direccion es %p en ft_cd.c en linea 28\n", result);
	if (!result)
		return (NULL);
	ft_strcpy(result, base_path);
	if (result[base_len - 1] != '/')
		ft_strcat(result, "/");
	ft_strcat(result, relative_path);
	//printf(ORANGE"direccion es %p en ft_cd.c en linea 35 y base_path es [%s]\n", result, base_path);
	//printf(ORANGE"direccion es %p en ft_cd.c en linea 35 y relative_path es [%s]\n", result, relative_path);
	return (result);
}

int	change_directory_loop(char *cur_path)
{
	if (chdir(cur_path) == -1)
	{
		//printf(RED"cur_path en change_directory_loop es [%s]\n"RESET, cur_path);
		//printf("entra en el if\n");
		return (-1);
	}
	return (0);
}

int	change_directory(char *path, char *old_path, int i)
{
	char	*cur_path;

	if (i == 0)
	{
		//printf(GREEN"path es [%s] en ft_cd.c en linea 60\n"RESET, path);
		cur_path = ft_strdup(path + 7);
		//printf(GREEN"cur_path es [%s] y su direccion es %p en ft_cd.c en linea 64\n"RESET, cur_path, cur_path);
		if (change_directory_loop(cur_path) == -1)
			return (free(path), -1);
		free (cur_path);
	}
	if (is_absolute_path(path) && i == 1)
	{
		printf(GREEN"direccion de path es %p en ft_cd.c linea 79\n"RESET, path);
		cur_path = path;
		//printf(GREEN"direccion de path es %p en ft_cd.c en linea 65\n"RESET, path);
		printf(GREEN"direccion es %p en ft_cd.c en linea 65\n"RESET, cur_path);
	}
	else
	{
		cur_path = build_relative_path(old_path, path);
		if (!cur_path)
			return (err_cd_msg("", 1), -1);
		free (cur_path);
	}
	//printf(ROSE"old_path es [%s] y su direccion es %p en ft_cd.c en linea 58\n"RESET, old_path, old_path);
	printf(GREEN"direccion es %p en ft_cd.c linea 79\n"RESET, path);
	if (i == 1 && chdir(cur_path) == -1)
	{
		if (access(cur_path, F_OK) == -1)
			return (err_cd_msg(cur_path, 4), -1);
		if (access(cur_path, R_OK | X_OK) == -1)
			return (err_cd_msg(cur_path, 2), -1);
		free (cur_path);
	}
	else if (i == 1)
		free (cur_path);
	//printf(ROSE"home su direccion es %p en ft_cd.c en linea 88\n"RESET, cur_path);
	//free(cur_path);
	//printf(GREEN"direccion es %p en ft_cd.c linea 87\n", cur_path);
	return (0);
}

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
		//printf(ORANGE"direccion es %p en ft_cd.c en linea 104\n", current);
	}
	else if (!ft_strncmp(token->args[1], "-", 1))
	{
		actual_path = search_var_in_env("OLDPWD", env);
		//printf(GREEN"actual_path es [%s] y su direccion es %p en ft_cd.c en linea 110\n", actual_path, actual_path);
		change_directory(actual_path, *old, 0);
		free (actual_path);
		ft_pwd(1);
	}
	else if (change_directory(token->args[1], *old, 1) == -1)
		return (free_cd(*old, *current, 1), -1);
	//printf(GREEN"home es [%s] y su direccion es %p en ft_cd.c linea 119\n", home, home);
	printf(GREEN"old es [%s] y su direccion es %p en ft_cd.c linea 119\n", *old, &token->args[1]);
	home = NULL;
	return (0);
}

int	ft_cd(t_token *token, char **env)
{
	char	*cur_path;
	char	*tmp;
	char	*old_path;
	int		result;

	if (search_var_in_env("HOME", env) == NULL)
		return (err_cd_msg("", 3), -1);
	old_path = getcwd(NULL, PATH_MAX);
	if (token->args[1] && ft_strncmp(token->args[1], "..", 2) == 0)
	{
		if (token->next && token->next->type == PIPE)
			return (0);
		cur_path = substring_before_last_slash(old_path);
	}
	else
	{
		cur_path = ft_strjointhree(old_path, "/", token->args[1]);
		printf(ORANGE"direccion es %p en ft_cd.c en linea 142\n"RESET, &token->args[1]);
	}
	result = handle_special_cases(env, &old_path, &cur_path, token);
	//printf(ORANGE"direccion es %p en ft_cd.c en linea 145\n", result);
	if (result != 0)
		return (result);
	tmp = ft_pwd_cd();
	set_var_in_env("OLDPWD", old_path, env);
	set_var_in_env("PWD", tmp, env);
	//printf("direccion de old_path en ft_cd.c linea 152 es %p\n", old_path);
	return (free_cd(old_path, cur_path, 2), 0);
}
