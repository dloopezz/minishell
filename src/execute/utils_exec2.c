/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:35:54 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/30 15:10:22 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	{
		perror("error opening file\n");
		g_exit_code = 1;
		exit(EXIT_FAILURE);
	}
	return (fd_ret);
}

void	check_infile(t_token *token, t_data *data, int fd_inf)
{
	if (token->next && (data->infile || data->del))
	{
		if (data->llt && ft_strcmp(data->llt, "<<") == 0)
			fd_inf = data->heredc->fd[READ];
		else if (data->lt && ft_strcmp(data->lt, "<") == 0)
			fd_inf = open_file(data->infile, 0);
		if (dup2(fd_inf, STDIN_FILENO) == -1)
		{
			perror("Error duplicating file descriptor");
			g_exit_code = 1;
			exit(EXIT_FAILURE);
		}
		if (close(fd_inf) == -1)
		{
			perror("Error closing file descriptor");
			g_exit_code = 1;
			exit(EXIT_FAILURE);
		}
	}
	else if (fd_inf != STDIN_FILENO)
	{
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
}

void	check_outfile(t_token *token, t_data *data, int fd_outf)
{
	if (fd_outf != STDOUT_FILENO)
	{
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);
	}
	else if (token->next && (data->outfile))
	{
		if (ft_strcmp(data->gt, ">") == 0)
			fd_outf = open_file(data->outfile, 1);
		else if (ft_strcmp(data->ggt, ">>") == 0)
			fd_outf = open_file(data->outfile, 2);
		if (dup2(fd_outf, STDOUT_FILENO) == -1)
		{
			perror("Error duplicating file descriptor");
			g_exit_code = 1;
			exit(EXIT_FAILURE);
		}
		if (close(fd_outf) == -1)
		{
			perror("Error closing file descriptor");
			g_exit_code = 1;
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_exec_builtins(t_token *token, t_data *data)
{
	int	fd[2];

	pipe(fd);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (!ft_fork())
	{
		close(fd[READ]);
		if (data->outfile != NULL)
			check_outfile(token, data, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		builtin(token->args[0], token, data, STDOUT_FILENO);
		exit(0);
	}
	close(fd[WRITE]);
	return (fd[READ]);
}

int	prueba_builtin(t_token *token, t_data *data)
{
	while (token)
	{
		if ((!token->next) && data->outfile == NULL)
		{
			builtin(token->args[0], token, data, STDOUT_FILENO);
			return (STDIN_FILENO);
		}
		else
			return (ft_exec_builtins(token, data));
		token = token->next;
	}
	return (STDIN_FILENO);
}
