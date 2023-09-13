/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:56:23 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 15:46:39 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * It checks if the command is in the current directory, if it is, it returns
 * the command, if it's not, it checks if the command is in the PATH, if it 
 * is, it returns the command, if it's not, it exits with an error
 * 
 * @param path a double pointer to the path
 * @param cmd The command that the user entered.
 * @param av the name of the program
 * 
 * @return the full path of the command.
 */
static char	*found_cmd(char **path, char **cmd, char *av)
{
	char	*fcmd;

	if (access(cmd[0], X_OK) == 0)
	{
		double_pointer_free(path);
		fcmd = ft_strjoin("", cmd[0]);
		return (fcmd);
	}
	if (ft_strchr(cmd[0], '/') && access(cmd[0], X_OK) != 0)
	{
		double_pointer_free(cmd);
		double_pointer_free(path);
		exit_error(NO_INFILE, av, 127);
	}
	fcmd = checkcommand_in_path(path, cmd[0]);
	if (fcmd != NULL)
	{
		return (fcmd);
	}
	double_pointer_free(cmd);
	double_pointer_free(path);
	exit_error(COM_ERR, fcmd, 127);
	return (NULL);
}

/**
 * It opens the file given as the first argument, duplicates the file 
 * descriptor to the standard input, closes the file descriptor, duplicates 
 * the write end of the pipe to the standard output, closes the pipe, and 
 * then executes the command given as the second argument
 * 
 * @param path a double pointer containing the path of the command
 * @param argv the arguments passed to the program
 * @param fd_pipe the pipe file descriptor
 * @param envp the environment variables
 */
static void	child1(char **path, char **argv, int *fd_pipe, char **envp)
{
	char	*path_cmd;
	char	**cmd;
	int		fd_input;

	fd_input = open(argv[1], O_RDONLY);
	if (fd_input == -1)
	{
		double_pointer_free(path);
		exit_error(NO_INFILE, argv[1], errno);
	}
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	cmd = ft_split(argv[2], ' ');
	path_cmd = found_cmd(path, cmd, argv[2]);
	if (execve(path_cmd, cmd, envp) == -1)
	{
		free(path_cmd);
		double_pointer_free(cmd);
		exit (errno);
	}
}

/**
 * It's a child process that reads from the pipe and writes to a file
 * 
 * @param path a double pointer containing all the paths in the PATH 
 * environment variable
 * @param argv the arguments passed to the program
 * @param fd_pipe the pipe file descriptor
 * @param envp the environment variables
 */
static void	child2(char **path, char **argv, int *fd_pipe, char **envp)
{
	char	*new_cmd;
	char	**cmd;
	int		fd_output;

	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		double_pointer_free(path);
		exit_error(NO_OUTFILE, argv[4], errno);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	cmd = ft_split(argv[3], ' ');
	new_cmd = found_cmd(path, cmd, argv[3]);
	if (execve(new_cmd, cmd, envp) == -1)
	{
		free(new_cmd);
		double_pointer_free(cmd);
		exit (errno);
	}
}

/**
 * It takes the PATH environment variable and splits it into an array of 
 * strings, each of which is a directory
 * 
 * @param envp The environment variables.
 * 
 * @return a pointer to a pointer to a char.
 */
char	**checkpath(char **envp, char **argv)
{
	char	**path = NULL;
	char	*tmp = NULL;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (access(argv[2], X_OK) == 0)
	{
		tmp = ft_strdup(argv[2]);
		j = 0;
	}
	if (!*envp && j != 0)
			exit_error(7, *envp, 127);
	while (!tmp && envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
	}
	if (!tmp)
		tmp = ft_strtrim(envp[i], "PATH=");
	path = ft_split(tmp, ':');
	if (tmp)
		free(tmp);
	i = 0;
	while (path[i])
	{
		free (path[i]);
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

/**
 * It forks twice, the first child executes the first command, the second child
 * executes the second command, the parent waits for both children to finish 
 * and returns the exit status of the second child
 * 
 * @param argc the number of arguments passed to the program
 * @param argv the arguments passed to the program
 * @param envp the environment variables
 * @return The return value of the second child process.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

	if (argc != 5)
		exit_error(ARG_ERR, NULL, 1);
	pipex.path = checkpath(envp, argv);
	/* for (int i = 0; pipex.path[i]; i++)
		printf("path[%d] is %s\n",i, pipex.path[i]); */
	if (pipe(pipex.fd_pipe) == -1)
		exit_error(PIPE_ERR, NULL, errno);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit_error(FORK_ERR, NULL, errno);
	if (pipex.pid1 == 0)
		child1(pipex.path, argv, pipex.fd_pipe, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit_error(FORK_ERR, NULL, errno);
	if (pipex.pid2 == 0)
		child2(pipex.path, argv, pipex.fd_pipe, envp);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);
	double_pointer_free(pipex.path);
	waitpid(pipex.pid1, &pipex.status, 0);
	waitpid(pipex.pid2, &pipex.status, 0);
	return (WEXITSTATUS(pipex.status));
}
