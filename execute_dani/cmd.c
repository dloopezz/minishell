/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:30:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/12 11:32:49 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx2(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

int	find_path_pos2(char **env)
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

char	*find_path2(char *cmd, char **env)
{
	char	**all_dir;
	char	*slash_cmd;
	char	*path;
	int		pos;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pos = find_path_pos2(env);
	all_dir = ft_split(env[pos] + 5, ':');
	i = -1;
	while (all_dir[++i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		path = ft_strjoin(all_dir[i], slash_cmd);
		free(slash_cmd);
		if (access(path, X_OK) == 0)
		{
			free_mtx(all_dir);
			return (path);
		}
		free(path);
	}
	free_mtx(all_dir);
	return (0);
}

void	ft_execve(t_token *tokens, t_data *data, int fdin, int fdout)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		path = find_path2(tokens->args[0], data->envi);
		if (!path)
			exit (127);
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		// printf("EXEC: |%s|\n", tokens->args[0]);
		if (execve(path, tokens->args, data->envi) == -1)
			exit(1);
	}
	else
		waitpid(pid, &status, 0);
}

void	process_cmd(t_token *tokens, t_data *data, int fdin, int fdout)
{
	//error handle
	//handle builtins
	// read_list(tokens);
	
	// t_token *aux_lst = tokens;
	// while (aux_lst)
	// {
	// 	printf("\n\033[33mNEW ARG: \033[0m\n");
	// 	printf("TOKEN: %s\n", aux_lst->args[0]);
	// 	aux_lst = aux_lst->next;
	// }
	// printf("\n");

	if (!builtin(tokens->args[0], tokens, data, fdout))
		ft_execve(tokens, data, fdin, fdout);

}

