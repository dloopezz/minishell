/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:44 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/08 18:24:47 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(t_token *token)
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

int	ft_exec_builtins(t_token *token, t_data *data)
{
	int	fd[2];
	
	pipe(fd);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if(!ft_fork())
	{
		close(fd[READ]);
		if (token->next->next->type == OUTFILE)
			check_outfile(token, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		ft_builtin(token, data);
		exit(0);
	}
	close(fd[WRITE]);
	return (fd[READ]);
}

int prueba_builtin(t_token *token, t_data *data)
{
	while (token)
	{
		/* if (!token->next || (token->type != CMD && token->type != GT))
		{
			printf("token next type es %d\n", token->type);
			printf("token next es %s\n", *token->args);
			printf("entra\n");
			return (ft_builtin(token, data));
		} */
		if (ft_is_builtin(token))
			return(ft_exec_builtins(token, data));
		token = token->next;
	}
	return (STDIN_FILENO);
}

int	ft_builtin(t_token *tokens, t_data *data)
{
	if (ft_strncmp(tokens->args[0], "cd\0", 3) == 0)
		return (ft_cd(tokens, data->envi));
	if (ft_strncmp(tokens->args[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(tokens->args[0], "echo\0", 5) == 0)
		return (ft_echo(tokens));
	if (ft_strncmp(tokens->args[0], "env\0", 4) == 0)
		return (ft_env(data, tokens));
	if (ft_strncmp(tokens->args[0], "export\0", 7) == 0)
		return (ft_export(tokens, data));
	if (ft_strncmp(tokens->args[0], "unset\0", 6) == 0)
		return (ft_unset(tokens, data));
	if (ft_strncmp(tokens->args[0], "exit\0", 5) == 0)
		return (ft_exit(tokens->args));
	return (-1);
}
