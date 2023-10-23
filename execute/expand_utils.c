/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/20 15:11:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_single_quotes(char *str, int *len)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] != SINGLE_QUOTES)
	{
		i++;
		(*len)++;
	}
	(*len)++;
	return (i);
}

int	process_double_quotes(char *str, int *len, char **env)
{
	int i = 1;
	(*len)++;
	while (str[i] && str[i] == '$')
		i += check_init_dollar(&str[i], len, NULL, env);
	if (str[i] == '\0')
		return (i);
	while (str[i] && str[i] != DOUBLE_QUOTES)
	{
		while (str[i] && str[i] == '$')
			i += check_init_dollar(&str[i], len, NULL, env);
		if (str[i] == '\0')
			return (i);
		(*len)++;
		i++;
	}
	(*len)++;
	return (i);
}

int doub_quotes(char *str, int *i, int *n_char, char *str_exp, t_data *env)
{
    str_exp[(*n_char)++] = str[(*i)++];
    while (str[*i] && str[*i] == '$')
        (*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
    if (str[*i] == '\0')
        return (1);
    while (str[*i] && str[*i] != DOUBLE_QUOTES)
    {
        while (str[*i] && str[*i] == '$')
            (*i) += check_init_dollar(&str[*i], n_char, str_exp, env->envi);
        if (str[*i] == '\0')
            return (1);
        str_exp[(*n_char)++] = str[(*i)++];
    }
    str_exp[(*n_char)++] = str[(*i)++];
    return (0);
}

int sing_quotes(char *str, int *i, int *n_char, char *str_exp)
{
	str_exp[(*n_char)++] = str[(*i)++];
	while (str[*i] && str[*i] != SINGLE_QUOTES)
	{
		str_exp[(*n_char)++] = str[(*i)++];
		if (str[*i] == '\0')
			return (1);
	}
	str_exp[(*n_char)++] = str[(*i)++];
	return (0);
}

/* int	ft_cd(t_token *token, char **env)
{
	char *home;
	char *current_path;
	char *old_path;

	home = get_home(env);
	old_path = getcwd(NULL, PATH_MAX);
	set_var_in_env("OLDPWD", old_path, env);
	current_path = ft_strjoin(old_path, "/");
	current_path = ft_strjoin(current_path, token->args[1]);
	if (!token->args[1] || token->args[1][0] == '~')
	{
		if (chdir(home) == -1)
			ft_clear_data_cd(old_path, current_path, 1);
		current_path = ft_strdup(home);
	}
	else
	{
		if (is_absolute_path(token->args[1]))
			current_path = ft_strdup(token->args[1]);
		else
		{
			current_path = build_relative_path(old_path, token->args[1]);
			if (!current_path)
			{
				perror("build relative path");
				ft_clear_data_cd(old_path, current_path, 1);
			}
		}
		if (chdir(current_path) == -1)
			ft_clear_data_cd(old_path, current_path, 2);
	}
	set_var_in_env("PWD", current_path, env);
	ft_clear_data_cd(old_path, current_path, 3);
	return (0);
}
void ft_clear_data_cd(char *old_path, char *current_path, int i)
{
	if (i == 1)
		free (old_path);
	else if (i == 2)
	{
		free (old_path);
		free (current_path);
		retu
	}
	else if (i == 2)
	{
		free (old_path);
		free (current_path);
	}
} */