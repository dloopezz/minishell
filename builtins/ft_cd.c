/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/15 11:43:47 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(char **env)
{
	char	*home_path;
	char	*return_path;

	home_path = search_var_in_env("HOME", env);
	if (!home_path)
		error_arg_msg("HOME not set\n", 4);
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
			return (err_cd_msg(1), -1);
	}
	if (i == 1 && chdir(cur_path) == -1)
		return (err_cd_msg(2), -1);
	return (0);
}

void	virg_exp(char **cur_path, char *token_arg, char *home, char *old_path)
{
	char	*line;
	char	*linedef;

	line = token_arg;
	linedef = ft_strdup("");
	while (line)
	{
		if (!ft_strncmp(line, "~/", 2))
		{
			linedef = ft_strdup(line + 1);
			ft_strtrim(linedef, "/");
			free(line);
		}
		break ;
	}
	*cur_path = ft_strjointhree(home, "/", linedef);
	*cur_path = ft_strjoin(*cur_path, "/");
	change_directory(*cur_path, old_path, 1);
}

//TODO revisar codigo de retorno de error
int	ft_cd(t_token *token, char **env)
{
	char	*home;
	char	*cur_path;
	char	*actual_path;
	char	*old_path;

	home = get_home(env);
	old_path = getcwd(NULL, PATH_MAX);
	actual_path = search_var_in_env("OLDPWD", env);
	set_var_in_env("OLDPWD", old_path, env);
	cur_path = ft_strjointhree(old_path, "/", token->args[1]);
	if (!token->args[1] || (token->args[1][0] == '~'
		&& token->args[1][2] == '\0') || !ft_strncmp(token->args[1], "--", 2))
	{
		if (chdir(home) == -1)
			return (ft_clear_cd(old_path, cur_path, 1), -1);
		cur_path = ft_strdup(home);
	}
	else if (!ft_strncmp(token->args[1], "-", 1))
		change_directory(actual_path, cur_path, 0);
	else if (!ft_strncmp(token->args[1], "~/", 2))
		virg_exp(&cur_path, token->args[1], home, old_path);
	else if (change_directory(token->args[1], old_path, 1) == -1)
		return (ft_clear_cd(old_path, cur_path, 1), -1);
	set_var_in_env("PWD", cur_path, env);
	return (ft_clear_cd(old_path, cur_path, 2), 0);
}
