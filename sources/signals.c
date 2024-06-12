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

void	save_free_data(t_data *data, char *str, int status)
{
	static t_data	*data_save;
	static char		*str_save;

	if (status)
	{
		data_save = data;
		str_save = str;
	}
	else
		free_all(data_save, str_save, 0);
}

void	signal_heredoc(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		printf("\n");
		fd = open(".tmp.txt", O_TRUNC);
		close(fd);
		save_free_data(NULL, NULL, 0);
		exit(130);
	}
}

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_return_value(130);
		printf("\r");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
