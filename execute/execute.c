/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:53:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/28 17:02:18 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

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

char	*find_path(char *cmd, char **env)
{
	char	**all_dir;
	char	*slash_cmd;
	char	*path;
	int		pos;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pos = find_path_pos(env);
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

void	exec_cmd(t_token *token, char **env)
{
	char	*path;

	path = find_path(token->args[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*token->args, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	if (execve(path, token->args, env) == -1)
		exit (1);
}

// void	child_process(char *cmd, char *env[])
// {
// 	pid_t	id;
// 	int		end[2];

// 	pipe(end);
// 	if (end < 0)
// 		exit (EXIT_FAILURE);
// 	id = fork();
// 	if (id < 0)
// 		exit(EXIT_FAILURE);
// 	if (id == 0)
// 	{
// 		dup2(end[1], STDOUT_FILENO);
// 		close(end[1]);
// 		exec_cmd(cmd, env);
// 	}
// 	else
// 	{
// 		close(end[1]);
// 		dup2(end[0], STDIN_FILENO);
// 		waitpid(id, 0, 0);
// 	}	
// 	close(end[1]);
// 	close(end[0]);
// }


void	exec_one_cmd(t_token *token, char **env)
{
	pid_t	id;
	int	status;

	id = fork();
	if (id < 0)
		exit(EXIT_FAILURE);
	if (id == 0)
	{
		sig_child();
		if (WIFSIGNALED(status))
			waitpid(id, &status, 0);
				if (WTERMSIG(status) == 3)
					write(1, "Quit: 3", 7);
		exec_cmd(token, env);
	}
	waitpid(id, &status, 0);
}

void	ft_execute(t_token *token, t_data *data)
{
	pid_t	id;
	int	status;
	int	outfile;
	int	infile;
	int end[2];

	if (!token->next)
	{
		exec_one_cmd(token, data->envi);
		return ;
	}
	while (token->next)
	{
		
		pipe(end);
		if (end < 0)
			exit (EXIT_FAILURE);

		id = fork();
		if (id < 0)
			exit(EXIT_FAILURE);
			
		if (id == 0)
		{
			// sig_child();
			// if (WIFSIGNALED(status))
			// {
			// 	waitpid(id, &status, 0);
			// 	if (WTERMSIG(status) == 3)
			// 		write(1, "Quit: 3", 7);
			// }
			if (token->next && token->next->type == PIPE)
			{
				dup2(end[1], STDOUT_FILENO);
				close(end[1]);
			}
			else if (token->next && token->next->type == GT)
			{
				outfile = open(token->next->next->args[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(outfile, STDOUT_FILENO);
			}
			else if (token->next && token->next->type == LT)
			{
				infile = open(token->next->next->args[0], O_RDONLY, 0644);
				dup2(infile, STDIN_FILENO);
			}
			exec_cmd(token, data->envi);
		}
		else
		{
			if (token->next && token->next->type == PIPE)
			{
				close(end[1]);
				dup2(end[0], STDIN_FILENO);
				waitpid(id, 0, 0);
			}
			if (token->next && (token->next->type == LT || token->next->type == GT || token->next->type == PIPE))
				token = token->next->next;
			else
				token = token->next;
			if (token->prev && token->prev->type == PIPE) //hay que ponerlo pero peta prev con solo ls
			{	
				close(end[0]);
				close(end[1]);
				exec_one_cmd(token, data->envi);
				printf("TOKEN: %s\n", token->args[0]);
				waitpid(id, 0, 0);
			}
		}
	}

	// pipex(tokens, data->envi);
	printf("ENTRA\n");
	waitpid(id, &status, 0);
	
}
// void	ft_execute(t_token *token, t_data *data)
// {
// 	pid_t	id;
// 	int	status;
// 	int	outfile;
// 	int	infile;
// 	int end[2];

// 	//al meterlo en un bucle, cuando vuelve a entrar esta en el file y da error de cmd not found
// 	while (token)
// 	{
// 		id = fork();
// 		if (id < 0)
// 			exit(EXIT_FAILURE);
	
// 		pipe(end);
// 		if (end < 0)
// 			exit (EXIT_FAILURE);
			
// 		if (id == 0)
// 		{
// 			sig_child();
// 			if (WIFSIGNALED(status))
// 			{
// 				waitpid(id, &status, 0);
// 				if (WTERMSIG(status) == 3)
// 					write(1, "Quit: 3", 7);
// 			}


// 			if (token->next && token->next->type == PIPE)
// 			{
// 				// child_process()
// 				// dup2(end[1], STDOUT_FILENO);
// 				// close(end[1]);
// 				// exec_cmd(token, data->envi);
// 			}
// 			else if (token->next && token->next->type == GT)
// 			{
// 				outfile = open(token->next->next->args[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
// 				dup2(outfile, STDOUT_FILENO);
// 			}
// 			else if (token->next && token->next->type == LT)
// 			{
// 				infile = open(token->next->next->args[0], O_RDONLY, 0644);
// 				dup2(infile, STDIN_FILENO);
// 			}
			
// 			exec_cmd(token, data->envi);
// 		}
// 		if (token->next && (token->next->type == LT || token->next->type == GT || token->next->type == PIPE))
// 			token = token->next->next;
// 		else
// 			token = token->next;
// 	}

// 	// pipex(tokens, data->envi);
// 	waitpid(id, &status, 0);
// }
