/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:00:07 by crtorres          #+#    #+#             */
/*   Updated: 2024/01/28 12:12:44 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	signal_input(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sign(void)
{
	signal(SIGINT, &signal_input);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_parent(void)
{
	signal(SIGINT, &signal_input);
	signal(SIGQUIT, SIG_IGN);
}
