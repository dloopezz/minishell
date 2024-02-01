/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:51:31 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/02/01 15:08:23 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	disable_ctrl_c_hotkey(t_data *data)
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

void	shell_level(t_data **data)
{
	int		i;
	char	*tmp;
	char	*value;
	char	*nb;

	tmp = get_env("SHLVL", (*data)->envi);
	value = ft_itoa(1);
	if (!tmp)
	{
		(*data)->envi = set_var_in_env("SHLVL", value, (*data)->envi);
		free (value);
		return ;
	}
	free (value);
	value = search_shlvar_in_env("SHLVL", (*data)->envi);
	i = 0;
	if (tmp)
	{
		i = ft_atoi(value) + 1;
		nb = ft_itoa(i);
		(*data)->envi = set_var_in_env("SHLVL", nb, (*data)->envi);
		free(nb);
		free(value);
	}
}

int	check_unclosed_quotes(t_data *data, int flag)
{
	t_token	*aux;

	aux = data->tokens;
	while (aux)
	{
		if (aux->quotes == UNCLOSED)
		{
			free(data->line);
			data->line = NULL;
			flag = 1;
		}
		aux = aux->next;
	}
	return (flag);
}

int	init_rl(t_data **data)
{
	(*data)->break_flag = 0;
	(*data)->i_rl = 0;
	(*data)->line = readline("\033[33m\u263B\033[36m > \033[0m");
	if (!(*data)->line)
		return (0);
	return (1);
}
