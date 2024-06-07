/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:19:38 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/04 13:44:20 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_pipes(t_data *data, unsigned int nb_pipes, int *pipe_fds)
{
	unsigned int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			perror("Pipe opening error:\n");
			i = i * 2;
			while (i > 0)
				close(pipe_fds[--i]);
			exit(free_all(data, NULL, 0, EXIT_FAILURE));
		}
		i++;
	}
	i = i * 2;
	while (i > 0)
		close(pipe_fds[--i]);
}

static void	wait_parent(t_data *data, int *pipe_fds)
{
	unsigned int	i;
	int				sig;
	int				status;

	i = 3;
	status = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	while (waitpid(0, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			set_return_value(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == 3)
				ft_putstr_fd("Quit (core dumped)\n", 2);
			if (sig == 2)
				printf("\r");
		}
	}
}

void	pipes_commands(t_data *data, t_command *command,
						unsigned int i)
{
	data->pipe_fds = NULL;
	if (data->nb_pipes)
	{
		data->pipe_fds = malloc(sizeof(int) * (data->nb_pipes * 2));
		if (!data->pipe_fds)
		{
			perror("minishell: malloc: ");
			return ;
		}
		open_pipes(data, data->nb_pipes, data->pipe_fds);
	}
	while (command)
	{
		set_return_value(0);
		if (!exec_builtins(data, command))
			child(data, command, data->pipe_fds, i);
		command = command->next;
		i += 2;
	}
	wait_parent(data, data->pipe_fds);
	ft_free(data->pipe_fds);
}
