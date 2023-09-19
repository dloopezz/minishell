/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:25:38 by crtorres          #+#    #+#             */
/*   Updated: 2023/08/10 17:31:41 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	double_pointer_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free (ptr);
}

/**
 * It opens a file, and returns the file descriptor
 * 
 * @param file the file to open
 * @param type 0 for input, 1 for output, 2 for append
 * 
 * @return The file descriptor.
 */
int	open_file(char *file, int type)
{
	int	fd_ret;

	if (type == 0)
		fd_ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 2)
		fd_ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ret == -1)
		exit(0);
	return (fd_ret);
}

/**
 * It prints an error message and exits the program
 * 
 * @param err the error number
 * @param msg the error message to be displayed
 * @param errnum The error number that will be returned to the shell.
 */
void	exit_error(int err, char *msg, int errnum)
{
	if (err == 1)
		ft_putstr_fd("Invalid number of arguments\n", 2);
	else if (err == 2)
		perror("Pipe error :");
	else if (err == 3)
		perror("Fork error:");
	else if (err == 4)
		perror("no such file or directory :");
	else if (err == 5)
		msg = ft_strjoin(msg, ": no such file or directory");
	else if (err == 6)
		perror("command not found :");
	else if (err == 7)
		perror("here_doc error :");
	else if (err == 8)
		ft_putstr_fd("Command not found\n", 2);
	exit (errnum);
}

/**
 * It takes a string and an array of strings, and returns the value of the 
 * string in the array of strings
 * 
 * @param name the name of the environment variable you want to get
 * @param envp the environment variables
 * 
 * @return The value of the environment variable.
 */
char	*my_env(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], STDIN_FILENO, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}
