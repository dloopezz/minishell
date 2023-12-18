/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/18 16:42:03 by crtorres         ###   ########.fr       */
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
		i = ft_atoi(value) + 1;
		nb = ft_itoa(i);
		set_var_in_env("SHLVL", nb, data->envi);
		free(nb);
		free(value);
	}
}

/* void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		len_mtx;

	atexit(ft_leaks);
	len_mtx = ft_matrix_len(envp);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	printf("\033[0;36m%s:%d -> `%p`\033[0m\n", "minishell.c", 73, data); //LEAKS
	data->line = ft_strdup("");
	data->envi = envp;
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
			continue ;
		check_slash(data->line);
		//check_some_syntax(data->line);
		add_history(data->line);
		data->line = ft_expand(data, data->line);
		data->tokens = ft_parsing(data->line, data->tokens);
		handle_sign();
		if (data->tokens)
			ft_execute(data->tokens, data);
		tcsetattr(0, 0, &data->termios);
		printf("LLEGA\n");
		// free_tokens(data->tokens);
		free(data->line);
	}
	// free_tokens(data->tokens);
	free_data(data);
	// free(data->line);
	rl_clear_history();
	printf("END MAIN\n");
	exit (0); //cambiar por exitcode
	return (0);
}
