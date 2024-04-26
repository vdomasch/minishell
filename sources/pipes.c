/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:19:38 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/17 15:19:41 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void open_pipes(unsigned int nb_pipes, int *pipe_fds)
{
	unsigned int i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			printf("Pipe opening error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	child(t_data *data, int *pipe_fds, unsigned int i)
{
	if (data->cmd_list->next)
	{
		printf("||%d||\n", i);
		if (dup2(pipe_fds[i + 1], 1) < 0)
		{
			printf("Error dup2 not last\n");
			exit(EXIT_FAILURE);
		}
	}
	if (i != 0)
	{
		printf("|%d|\n", i);
		if (dup2(pipe_fds[i - 2], 0) < 0)
		{
			printf("Error dup2 not first\n");
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	if (exec(data))
		printf("Error exec\n");
	return ;
}

void pipes_commands(t_data *data)
{
	//int				pid;
	unsigned int	i;
	int				pipe_fds[data->nb_pipes * 2];
	t_command		*command;

	i = 0;
	open_pipes(data->nb_pipes, pipe_fds);
	command = data->cmd_list;
	while (command)
	{
		//pid = fork();
		//if (pid == 0)
			child(data, pipe_fds, i);
		/*else if (pid < 0)
		{
			printf("Error fork\n");
			exit(EXIT_FAILURE);
		}*/
		command = command->next;
		i += 2;
	}
	//i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	//while(waitpid(0,0,0) < 0);
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
		exec(&data);
	return (0);
}*/
