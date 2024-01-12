/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/12 18:22:26 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	disable_ctrl_c_hotkey(t_data *data)
{
	int	rc;

	rc = tcgetattr(0, &data->termios);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	data->termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &data->termios);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	shell_level(t_data *data)
{
	int		i;
	char	*tmp;
	char	*value;
	char	*nb;

	tmp = get_env("SHLVL", data->envi);
	if (!tmp)
	{
		set_var_in_env("SHLVL", ft_itoa(1), data->envi);
		return ;
	}
	value = search_shlvar_in_env("SHLVL", data->envi);
	i = 0;
	if (tmp)
	{
		i = ft_atoi(value) + 1;
		nb = ft_itoa(i);
		set_var_in_env("SHLVL", nb, data->envi);
		free(nb);
		free(value);
	}
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		len_mtx;

	atexit(ft_leaks);
	len_mtx = ft_matrix_len(envp);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	data->line = ("");
	if (envp)
	{
		size_t len = ft_matrix_len(envp);
		data->envi = malloc(sizeof(data->envi) * (len + 1));
		for (size_t i = 0; i < len; i += 1)
		{
			data->envi[i] = ft_strdup(envp[i]);
		}
	}
	shell_level(data);
	disable_ctrl_c_hotkey(data);
	handle_sign();
	while (1)
	{
		data->line = NULL;
		data->line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (!data->line)
			break ;
		if (!data->line[0])
		{
			free (data->line);
			continue ;
		}
		check_slash(data->line);
		// check_some_syntax(data->line);
		add_history(data->line);
		data->line = ft_expand(data, data->line);
		data->tokens = ft_parsing(data->line, data->tokens);
		//TODO unclosed arreglado pero muchos leaks
		if (data->tokens->quotes  == UNCLOSED)
		{
			
			// printf("llega\n");
			free(data->line);
			data->line = NULL;
			free_tokens(data->tokens);
			system("leaks -q minishell");
			continue;
		}
		data->token_aux = data->tokens;
		handle_sign();
		read_list(data->tokens);
		if (data->tokens)
			ft_execute(data->tokens, data);
		tcsetattr(0, 0, &data->termios);
		free(data->line);
		data->line = NULL;
		free_tokens(data->tokens);
	}
	free_data(data);
	rl_clear_history();


	exit (g_exit_code);
	return (0);
}
