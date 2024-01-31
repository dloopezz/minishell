/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/31 15:28:41 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data	*init_data(t_data *data, char **envp)
{
	int	i;
	int	len_mtx;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	data->line = ("");
	len_mtx = ft_matrix_len(envp);
	data->envi = malloc(sizeof(data->envi) * (len_mtx + 1));
	if (!data->envi)
		return (0);
	if (envp)
	{
		i = -1;
		while (++i < len_mtx)
			data->envi[i] = ft_strdup(envp[i]);
		data->envi[i] = NULL;
	}
	return (data);
}

t_data	*expand_and_parse(t_data *data)
{
	data->line = ft_expand(data, data->line);
	data->tokens = NULL;
	data->op_flag = 0;
	data->tokens = ft_parsing(data->line, data, data->tokens);
	if (data->tokens == NULL)
		return (data);
	data->break_flag = check_unclosed_quotes(data, data->break_flag);
	return (data);
}

t_data	*exec_and_free(t_data *data)
{
	if (data->tokens)
		ft_exec(data->tokens, data);
	tcsetattr(0, 0, &data->termios);
	free(data->cmd);
	free_tokens(data->tokens);
	free(data->line);
	data->line = NULL;
	return (data);
}

void	minishell_loop(t_data *data)
{
	while (1)
	{
		data->break_flag = 0;
		data->i_rl = 0;
		data->line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (!data->line)
			break ;
		if (data->line[0] && data->line[data->i_rl] == ' ')
			while (data->line[data->i_rl] && data->line[data->i_rl] == ' ')
				data->i_rl++;
		if (!data->line[data->i_rl])
		{
			free(data->line);
			continue ;
		}
		add_history(data->line);
		data = expand_and_parse(data);
		if (data->break_flag == 1)
			continue ;
		handle_sign();
		if (check_some_syntax(data->tokens) == 0)
			data = exec_and_free(data);
		else
		{
			free_tokens(data->tokens);
			free(data->line);
		}
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// atexit(ft_leaks);
	(void)argc;
	(void)argv;
	data = NULL;
	data = init_data(data, envp);
	disable_ctrl_c_hotkey(data);
	shell_level(&data);
	handle_sign();
	minishell_loop(data);
	free_data(data);
	rl_clear_history();
	exit (g_exit_code);
	return (0);
}
