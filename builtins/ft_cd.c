/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/10 18:52:14 by crtorres         ###   ########.fr       */
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
	result = (char *)malloc(base_len + relative_len + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, base_path);
	printf("base es %s\n", base_path);
	if (result[base_len - 1] != '/')
		ft_strcat(result, "/");
	ft_strcat(result, relative_path);
	return (result);
}

void	ft_clear_cd(char *old_path, char *current_path, int i)
{
	if (i == 1)
		free (old_path);
	else if (i == 2)
	{
		free (old_path);
		free (current_path);
	}
}

int	change_directory(char *path, char *old_path)
{
	char	*cur_path;

	if (is_absolute_path(path))
		cur_path = ft_strdup(path);
	else
	{
		cur_path = build_relative_path(old_path, path);
		if (!cur_path)
		{
			err_cd_msg(1);
			return (-1);
		}
	}
	if (chdir(cur_path) == -1)
	{
		err_cd_msg(2);
		return (-1);
	}
	return (0);
}

//TODO revisar codigo de retorno de error
int	ft_cd(t_token *token, char **env)
{
	char	*home;
	char	*cur_path;
	char	*old_path;

	home = get_home(env);
	old_path = getcwd(NULL, PATH_MAX);
	set_var_in_env("OLDPWD", old_path, env);
	cur_path = ft_strjoin(old_path, "/");
	cur_path = ft_strjoin(cur_path, token->args[1]);
	if (!token->args[1] || (token->args[1][0] == '~' && token->args[1][1] != '/'))
	{
		if (chdir(home) == -1)
			return (ft_clear_cd(old_path, cur_path, 1), -1);
		cur_path = ft_strdup(home);
	}
/* 	if (!ft_strncmp(token->args[1], "~/", 2))
	{
		printf("aqui esta entrandoo\n");
		//cur_path = 
	} */
	else
	{
		if (change_directory(token->args[1], old_path) == -1)
			return (ft_clear_cd(old_path, cur_path, 1), -1);
	}
	set_var_in_env("PWD", cur_path, env);
	ft_clear_cd(old_path, cur_path, 2);
	return (0);
}
