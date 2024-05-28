/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:01:55 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/12 17:01:57 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_return_value = 130;
	}
}

void	signal_set(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_set_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
