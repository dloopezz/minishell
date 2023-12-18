/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/18 14:17:01 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_home(char **env)
{
	char	*home_path;
	char	*return_path;

	home_path = search_var_in_env("HOME", env);
	if (!home_path)
		return (NULL);
	return_path = ft_strdup(home_path + 5);
	return (return_path);
}

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
		return (NULL);
	ft_strcpy(result, base_path);
	if (result[base_len - 1] != '/')
		ft_strcat(result, "/");
	ft_strcat(result, relative_path);
	return (result);
}

int	change_directory(char *path, char *old_path, int i)
{
	char	*cur_path;
	int		j;

	if (i == 0)
	{
		cur_path = ft_strdup(path + 7);
		j = -1;
		while (cur_path[++j])
		if (chdir(cur_path) == -1)
			return (free(path), -1);
	}
	if (is_absolute_path(path) && i == 1)
		cur_path = ft_strdup(path);
	else
	{
		cur_path = build_relative_path(old_path, path);
		if (!cur_path)
			return (err_cd_msg("", 1), -1);
	}
	if (i == 1 && chdir(cur_path) == -1)
	{
		if (access(cur_path, F_OK) == -1)
			return (err_cd_msg(cur_path, 4), -1);
		else
		return (err_cd_msg(cur_path, 2), -1);
	}
	return (0);
}

char	*substring_before_last_slash(const char *path)
{
	size_t	last_slash;
	char	*new_str;

	last_slash = ft_strlen(path) - 1;
	while (last_slash > 0 && path[last_slash] != '/')
	  last_slash--;
	if (last_slash == 0)
	  return "";
	new_str = malloc(sizeof(char) * last_slash + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, path, last_slash);
	new_str[last_slash] = '\0';
	return (new_str);
}

//TODO revisar codigo de retorno de error
int	ft_cd(t_token *token, char **env)
{
	char	*home;
	char	*cur_path;
	char	*actual_path;
	char	*tmp;
	char	*old_path;

	if (search_var_in_env("PWD", env) == NULL)
		return (err_cd_msg("", 5), -1);
	home = get_home(env);
	old_path = getcwd(NULL, PATH_MAX);
	actual_path = search_var_in_env("OLDPWD", env);
	setvar_cd("OLDPWD", old_path, env);
	if (token->args[1] && ft_strncmp(token->args[1], "..", 2) == 0)
	{	
		if(token->next->type == PIPE)
			return (0);
		cur_path = substring_before_last_slash(old_path);
	}
	else
		cur_path = ft_strjointhree(old_path, "/", token->args[1]);
	if (!token->args[1] || !ft_strncmp(token->args[1], "--", 2))
	{
		if (chdir(home) == -1)
			return (free_cd(old_path, cur_path, 1), -1);
		cur_path = ft_strdup(home);
	}
	else if (!ft_strncmp(token->args[1], "-", 1))
	{
		change_directory(actual_path, old_path, 0);
		ft_pwd(1);
	}
	else if (change_directory(token->args[1], old_path, 1) == -1)
		return (free_cd(old_path, cur_path, 1), -1);
	tmp = ft_pwd_cd();
	return (setvar_cd("PWD", tmp, env), free_cd(old_path, cur_path, 2), 0);
}
