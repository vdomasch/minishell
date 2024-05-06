/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:19:38 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/17 15:19:41 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_pipes(unsigned int nb_pipes, int *pipe_fds)
{
	unsigned int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			printf("Pipe opening error\n");
			exit(1);
		}
		i++;
	}
}

static void	child(t_data *data, t_command *cmd, int *pipe_fds, unsigned int i)
{
	signal_set_child();
	if (cmd->next)
	{
		if (dup2(pipe_fds[i + 1], 1) < 0)
			exit(1);
	}
	if (i != 0)
	{
		if (dup2(pipe_fds[i - 2], 0) < 0)
			exit(1);
	}
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	if (exec(data, 0) == 1)
		printf("%s: command not found\n", data->cmd_list->v_cmd[0]);
	free_cmd_list(data->cmd_list);
	free_env(data->env_list, data->v_path);
	free(pipe_fds);
	free(data->message);
	exit(0);
}

void	pipes_commands(t_data *data, t_command *command, unsigned int i)
{
	int				pid;
	int				*pipe_fds;

	i = 0;
	pipe_fds = malloc(sizeof(int) * (data->nb_pipes * 2));
	if (!pipe_fds)
		return ;
	open_pipes(data->nb_pipes, pipe_fds);
	command = data->cmd_list;
	while (command)
	{
		pid = fork();
		if (pid == 0)
			child(data, command, pipe_fds, i);
		else if (pid < 0)
			exit(1);
		command = command->next;
		i += 2;
	}
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	while (waitpid(0, 0, 0) > 0)
		;
	free(pipe_fds);
}
/*
int main(int argc, char **argv, char **env)
{
	t_data 		data;
	t_command	cmd_list;
	t_command	command_list;
	t_command	command_2;
	char 		*array[] = {argv[2], argv[3], NULL};
	char		*array2[] = { argv[4], argv [5], NULL};
	char		*array3[] = { argv[6], argv[7], NULL};

	data.nb_pipes = 0;
	if (argv[1])
		data.nb_pipes = atoi(argv[1]);
	cmd_list.v_cmd = array;
	cmd_list.prev = NULL;
	cmd_list.next = &command_list;
	command_list.v_cmd = array2;
	command_list.prev = &cmd_list;
	command_list.next = &command_2;
	command_2.v_cmd = array3;
	command_2.prev = &command_list;
	command_2.next = NULL;
	data.cmd_list = &cmd_list;
	process_env(data, env);
	if (data.nb_pipes > 0)
		pipes_commands(&data);
	else
		execution(&data);
	return (0);
}*/