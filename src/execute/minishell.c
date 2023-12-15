/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/15 15:39:18 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	disable_ctrl_c_hotkey(void)
{
	int	rc;

	rc = tcgetattr(0, &g_var.termios);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	g_var.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &g_var.termios);
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

	tmp = getenv("SHLVL");
	if (!tmp)
	{
		set_var_in_env("SHLVL", ft_itoa(1), data->envi);
		return ;
	}
	value = search_shlvar_in_env("SHLVL", data->envi);
	i = 0;
	if (tmp)
	{
		i = atoi(value) + 1;
		set_var_in_env("SHLVL", ft_itoa(i), data->envi);
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
	int		i;
	int		len_mtx;
	char	*line;

	// atexit(ft_leaks);
	len_mtx = ft_matrix_len(envp);
	(void)argc;
	(void)argv;
	line = ft_strdup(""); //inicializacion a lo guarro
	data = ft_calloc(1, sizeof(t_data));
	data->envi = envp;
	data->env_copy = ft_calloc(len_mtx + 1, sizeof(char *));
	shell_level(data);
	disable_ctrl_c_hotkey();
	handle_sign();
	i = -1;
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (!line)
			return (0);
		while (!line[0])
			line = readline("\033[33m\u263B\033[36m > \033[0m");
		check_slash(line);
		//check_some_syntax(line);
		add_history(line);
		line = ft_expand(line, data);
		data->tokens = ft_parsing(line, data->tokens);
		while (++i < len_mtx)
			data->env_copy[i] = ft_strdup(envp[i]);
		handle_sign();
		if (data->tokens)
			ft_execute(data->tokens, data);
		tcsetattr(0, 0, &g_var.termios);
		free(line);
		// free_mtx(data->envi); //lo libera pero peta, leak es data->envi
	}
	return (0);
}
