/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 12:11:24 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

char	*get_path(t_token *token, char **env)
{
	size_t	i;
	char	*home_path;

	home_path = search_var_in_env("HOME", env);
	if (!home_path)
		error_arg_msg("HOME not set\n", 4);
	i = 1;
	while (token->arg[i])
	{
		if (ft_lstsize(token->arg) > 1)
			ft_putendl_fd("too many arguments\n", STDERR_FILENO);
		i++;
	}
	return (home_path);

}

int	ft_cd(t_token *token, char **env)
{
	char *home;
	char *current_path;
	char *old_path;

	home = get_path(token, env);
	old_path = getcwd(current_path, PATH_MAX);
	set_var_in_env("OLDPWD=", old_path, env);
	current_path = ft_strjoin(old_path, token->arg[1]);
	if (!token->arg)
	{
		if (chdir(home) = -1)
		{
			free(old_path);
			return (-1);
		}
	}
	if (!chdir(current_path))
	{
		
	}
	
}

/* int main()
{
	ft_cd()
} */