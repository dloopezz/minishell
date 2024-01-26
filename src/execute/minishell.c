/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/24 12:56:25 by crtorres         ###   ########.fr       */
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
	value = ft_itoa(1);
	if (!tmp)
	{
		set_var_in_env("SHLVL", value, data->envi);
		free (value);
		return ;
	}
	free (value);
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
	int		i;

	//atexit(ft_leaks);
	len_mtx = ft_matrix_len(envp);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	data->line = ("");
	data->envi = malloc(sizeof(data->envi) * (len_mtx + 1));
	if (!data->envi)
		return (-1);
	if (envp)
	{
		i = -1;
		if (len_mtx == 0)
			data->envi = envp;
		while (++i < len_mtx)
			data->envi[i] = ft_strdup(envp[i]);
		data->envi[i] = NULL;
	}
	disable_ctrl_c_hotkey(data);
	handle_sign();
	shell_level(data);
	while (1)
	{
		data->line = NULL;
		data->line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (!data->line)
			break ;
		if (!data->line[0] || data->line[0] == ' ')
		{
			free (data->line);
			continue ;
		}
		add_history(data->line);
		data->line = ft_expand(data, data->line);
		data->tokens = ft_parsing(data->line, data->tokens);

		//para comprobar comillas cerradas (sacar pa normi)
		int flag = 0;
		t_token *aux = data->tokens;
		while (aux)
		{
			if (aux->quotes == UNCLOSED)
			{
				free(data->line);
				data->line = NULL;
				// free_tokens(data->tokens);
				flag = 1; 
			}
			aux = aux->next;
		}
		if (flag == 1)
			continue;
		
		data->token_aux = data->tokens;
		handle_sign();
		read_list(data->tokens);
		if (data->tokens)
			ft_exec(data->tokens, data);
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
