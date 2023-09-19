/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:00:07 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/19 18:19:45 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_input(int sig, t_data *data)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	data->exit_code = 130;
}

void	handle_sign(void)
{
	signal(SIGINT, &signal);
	signal(SIGQUIT, SIG_IGN);
}
