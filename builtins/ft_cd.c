/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:22:21 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 13:05:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(t_token *token, char **env)
{
	size_t	i;
	char	*home_path;

	home_path = search_var_in_env("HOME", env);
	if (!home_path)
		error_arg_msg("HOME not set\n", 4);
	i = 1;
	while (token->args[i])
	{
		if (ft_matrix_len(token->args) > 1)
			ft_putendl_fd("too many arguments\n", STDERR_FILENO);
		i++;
	}
	return (home_path);

}
//TODO revisar codigo de retorno de error
int	ft_cd(t_token *token, char **env)
{
	char *home;
	char *current_path;
	char *old_path;

	home = get_home(token, env);
	old_path = getcwd(NULL, PATH_MAX);
	set_var_in_env("OLDPWD", old_path, env);
	current_path = ft_strjoin(old_path, "/");
	current_path = ft_strjoin(current_path, token->args[1]);
	set_var_in_env("PWD", current_path, env);
	if (!token->args)
	{
		if (chdir(home) == -1)
		{
			free(old_path);
			return (-1);
		}
	}
	if (chdir(current_path) == -1)
	{
			free(old_path);
			free(current_path);
			return (-1);	
	}
	return (0);
}

/* int main()
{
	ft_cd()
} */