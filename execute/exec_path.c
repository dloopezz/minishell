/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:39:45 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/05 14:37:04 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path_pos(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
	}
	error_msg("|path not found| ");
	exit (1);
}

char	*find_in_path(t_token *token, t_data *data)
{
	char	**all_dir;
	char	*slash_cmd;
	int		pos;
	int		i;
	t_token *tmp_p;

	tmp_p = token;
	if (access(*tmp_p->args, X_OK) == 0)
		return (*tmp_p->args);
	pos = find_path_pos(data->envi);
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

void 	ft_check_cmd_path(t_token *token, t_data *data)
{
	t_token	*tmp = token;
	
	while (tmp != NULL)
	{
		if (ft_is_builtin(tmp) == 0)
			return;
		else if (tmp->args && tmp->type == CMD && access(tmp->args[0],X_OK) != 0)
		{
			tmp->path = find_in_path(tmp, data);
			if (!tmp->path)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(token->args[0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
		}
		tmp = tmp->next;
	}
}
