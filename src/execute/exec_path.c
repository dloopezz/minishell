/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:35:29 by crtorres          #+#    #+#             */
/*   Updated: 2024/02/01 14:41:55 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*find_in_path(t_token *token, t_data *data)
{
	char	**all_dir;
	char	*slash_cmd;
	int		pos;
	int		i;
	t_token	*tmp_p;

	tmp_p = token;
	if (access(*tmp_p->args, X_OK) == 0)
		return (*tmp_p->args);
	pos = find_path_pos(data->envi);
	if (pos == -1)
		return (NULL);
	all_dir = ft_split(data->envi[pos] + 5, ':');
	i = -1;
	while (all_dir[++i])
	{
		slash_cmd = ft_strjoin("/", *tmp_p->args);
		tmp_p->path = ft_strjoin(all_dir[i], slash_cmd);
		free(slash_cmd);
		if (access(tmp_p->path, X_OK) == 0)
			return (free_mtx(all_dir), tmp_p->path);
		free(tmp_p->path);
	}
	free_mtx(all_dir);
	return (NULL);
}

int	ft_is_builtin(t_token *token, t_data *data)
{
	if (search_var_in_env("PATH", data->envi) != NULL)
	{
		if (is_absolute_path(*token->args) == 0)
		{
			if (token->path)
				free(token->path);
			token->path = find_in_path(token, data);
		}
	}
	if ((ft_strncmp(token->args[0], "cd\0", 3) == 0)
		|| (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		|| (ft_strncmp(token->args[0], "env\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "export\0", 7) == 0)
		|| (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		|| (ft_strncmp(token->args[0], "exit\0", 5) == 0))
		return (0);
	else
		return (1);
}

int	ft_is_builtin2(t_token *token)
{
	if ((ft_strncmp(token->args[0], "cd\0", 3) == 0)
		|| (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		|| (ft_strncmp(token->args[0], "env\0", 4) == 0)
		|| (ft_strncmp(token->args[0], "export\0", 7) == 0)
		|| (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		|| (ft_strncmp(token->args[0], "exit\0", 5) == 0))
		return (0);
	else
		return (1);
}

int	ft_check_cmd_path(t_token *token, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (ft_is_builtin2(tmp) == 0)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				return (0);
		}
		if (search_var_in_env("PATH", data->envi) == NULL)
			return (exec_exit_error(2, tmp->args[0]), -1);
		else if (tmp->args && tmp->type == CMD
			&& access(tmp->args[0], X_OK) != 0)
		{
			if (check_no_path(&data, &token, &tmp) == -1)
				return (-1);
		}
		else if (access(tmp->args[0], X_OK) == 0)
			tmp->path = ft_strdup(tmp->args[0]);
		tmp = tmp->next;
	}
	return (0);
}
