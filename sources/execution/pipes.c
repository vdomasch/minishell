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
	unsigned int	tmp;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			perror("Pipe opening error:\n");
			tmp = 0;
			while (tmp < i)
				close(pipe_fds[tmp++]);
			exit(free_all(data, NULL, EXIT_FAILURE));
		}
		i++;
	}
}

static void	wait_parent(t_data *data)
{
	int				sig;
	int				status;
	unsigned int	i;

	status = 0;
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(data->pipe_fds[i++]);
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
				printf("\n");
			if (sig == 2 || sig == 3)
				set_return_value(sig + 128);
		}
	}
}

static int	heredoc_fork(t_data *data, t_command *cmd, int i)
{
	int	pid;
	int	status;

	signal(SIGINT, &signal_heredoc);
	pid = fork();
	if (pid == 0)
		heredoc_init(data, cmd, i);
	else if (pid < 0)
		perror("minishell");
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
			{
				i = WEXITSTATUS(status);
				set_return_value(i);
			}
			signal_set();
		}
	}
	return (i);
}

int	here_document(t_data *data, t_command *cmd)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	if (!is_there_chr(cmd->cmd, '>') && !is_there_chr(cmd->cmd, '<'))
		return (0);
	cmd->input_redirection = redirection(cmd, '<', 0);
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<' && !is_in_quotes(cmd->cmd, i)
			&& cmd->cmd[i + 1] == '<')
			return_value = heredoc_fork(data, cmd, i);
		i++;
	}
	ft_free(cmd->input_redirection);
	cmd->input_redirection = NULL;
	return (return_value);
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
		if (here_document(data, command))
			break ;
		if (!exec_builtins(data, command))
			child(data, command, data->pipe_fds, i);
		dup2(data->stdin, STDIN_FILENO);
		command = command->next;
		i += 2;
	}
	wait_parent(data);
	ft_free(data->pipe_fds);
}
