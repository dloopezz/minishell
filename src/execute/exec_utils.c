/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:35:54 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/23 19:05:05 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void	check_infile(t_token *token, t_data *data, int fd_inf)
{
	printf("CHECK INFILE TOKEN %s\n", *token->args);
	if (token->next && (token->next->type == LT || token->next->type == LLT || token->type == LLT))
	{
		printf("entra en check_infile\n");
		if (token->next->type == LT)
			fd_inf = open_file(*token->next->next->args, 0);
		else if (token->next->type == LLT || token->type == LLT)
		{
			printf("here es %s\n", data->file_hd);
			fd_inf = open_file(data->file_hd, 0);
		}
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
	else if(fd_inf != STDIN_FILENO)
	{
		dup2(fd_inf, STDIN_FILENO);
		close(fd_inf);
	}
}

void	check_outfile(t_token *token, t_data *data, int fd_outf)
{
	//printf("token outfile es %s\n", *token->args);
	//printf("token next en outfile es %s y su tipo es %d\n", *token->next->args, token->next->type);
	//printf("token 3next en outfile es %s y su tipo es %d\n", *token->next->next->next->args, token->next->next->next->type);
	if (fd_outf != STDOUT_FILENO)
	{
		printf("entra en esta mierda\n");
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);
	}
	else if (token->next && (data->outfile))
	{
		printf("ENTRA en outfile\n");
		if (token->next->type == GT || token->next->next->type == GT || token->next->next->next->type == GT)
		{
			printf("data out es %s\n", data->outfile);
			printf("fd_out antes es %d\n", fd_outf);
			fd_outf = open_file(data->outfile, 1);
			printf("fd_out es %d\n", fd_outf);
		}
		else if (token->next->type == GGT)
			fd_outf = open_file(data->outfile, 2);	
		printf("SALE en outfile\n");
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);
	}
	/* if (fd_outf != STDOUT_FILENO)
	{
		printf("entra en esta mierda\n");
		dup2(fd_outf, STDOUT_FILENO);
		close(fd_outf);
	} */
}

int	ft_exec_builtins(t_token *token, t_data *data)
{
	int	fd[2];
	
	pipe(fd);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if(!ft_fork())
	{
		close(fd[READ]);
		//printf("outf en exec_builtins es %s\n", token->outf);
		if (data->outfile != NULL)
			check_outfile(token, data, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		builtin(token->args[0],token, data, STDOUT_FILENO);
		exit(0);
	}
	close(fd[WRITE]);
	return (fd[READ]);
}

int prueba_builtin(t_token *token, t_data *data)
{
	while (token)
	{
		if ((!token->next) && data->outfile == NULL)
		{
			builtin(token->args[0],token, data, STDOUT_FILENO);
			return (STDIN_FILENO);
		}
		else
		{
			//printf("outf en prueba_builtin es %s\n", token->outf);
			return (ft_exec_builtins(token, data));
		}
		token = token->next;
	}
	return (STDIN_FILENO);
}
