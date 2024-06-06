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

static void	open_pipes(unsigned int nb_pipes, int *pipe_fds)
{
	unsigned int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipe_fds + (2 * i)) < 0)
		{
			perror("Pipe opening error:\n");
			exit(1);
		}
		i++;
	}
}

static void	print_errors(char *str, char *str2, char *str3, int error)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	set_return_value(error);
}

static void	exec_errors(t_command *cmd)
{
	if (errno == 13 && chdir(*cmd->v_cmd) == -1)
		print_errors("minishell: ", cmd->v_cmd[0], ": Permission denied\n", 126);
	else if (errno == 13)
		print_errors("minishell: ", cmd->v_cmd[0], ": Is a directory\n", 126);
	else if (**cmd->v_cmd == '/' || (**cmd->v_cmd == '.' && **cmd->v_cmd + 1 == '/'))
		print_errors("minishell: ", cmd->v_cmd[0], ": No such file or directory\n", 127);
	else
		print_errors(NULL, cmd->v_cmd[0], ": command not found\n", 127);
}

static void	child_exec(t_data *data, t_command *cmd, int *pipe_fds,
						  unsigned int i)
{
	signal_set_child();
	if (exec_redirections(data, cmd) != 1)
	{
		if (cmd->next)
			if (dup2(pipe_fds[i + 1], STDOUT_FILENO) < 0)
				exit(1);
		if (i != 0)
			if (dup2(pipe_fds[i - 2], STDIN_FILENO) < 0)
				exit(1);
	}
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	if (exec(data, cmd, 0) == 1 && *cmd->v_cmd)
		exec_errors(cmd);
	free_cmd_list(data->cmd_list);
	free_env(data->env_list, data->v_path);
	free_env(NULL, data->env);
	rl_clear_history();
	ft_free(pipe_fds);
	ft_free(data->message);
	exit(set_return_value(0));
}

static void	child(t_data *data, t_command *cmd, int *pipe_fds, unsigned int i)
{
	int	pid;

	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pid == 0)
		child_exec(data, cmd, pipe_fds, i);
	else if (pid < 0)
		exit(1);
}

void	wait_parent(t_data *data, int *pipe_fds)
{
	unsigned int	i;
	int				sig;
	int				status;

	i = 0;
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
		open_pipes(data->nb_pipes, data->pipe_fds);
	}
	while (command)
	{
		if (!exec_builtins(data, command))
			child(data, command, data->pipe_fds, i);
		command = command->next;
		i += 2;
	}
	wait_parent(data, data->pipe_fds);
	ft_free(data->pipe_fds);
}
