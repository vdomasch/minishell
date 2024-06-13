/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:22:08 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/06 16:22:17 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		print_errors("minishell: ", cmd->v_cmd[0],
			": Permission denied\n", 126);
	else if (errno == 13)
		print_errors("minishell: ", cmd->v_cmd[0],
			": Is a directory\n", 126);
	else if (**cmd->v_cmd == '/' || (**cmd->v_cmd == '.'
			&& **cmd->v_cmd + 1 == '/'))
		print_errors("minishell: ", cmd->v_cmd[0],
			": No such file or directory\n", 127);
	else
		print_errors(NULL, cmd->v_cmd[0], ": command not found\n", 127);
}

static void	child_exec(t_data *data, t_command *cmd, int *pipe_fds,
						unsigned int i)
{
	signal_set_child();
	if (cmd->next)
		if (dup2(pipe_fds[i + 1], STDOUT_FILENO) < 0)
			exit(free_all(data, NULL, EXIT_FAILURE));
	if (i != 0)
		if (dup2(pipe_fds[i - 2], STDIN_FILENO) < 0)
			exit(free_all(data, NULL, EXIT_FAILURE));
	exec_redirections(data, cmd, 0);
	i = 0;
	while (i < 2 * data->nb_pipes)
		close(pipe_fds[i++]);
	close(data->stdin);
	if (exec(data, cmd, 0) == 1 && *cmd->v_cmd)
		exec_errors(cmd);
	free_all(data, NULL, 0);
	exit(set_return_value(0));
}

void	child(t_data *data, t_command *cmd, int *pipe_fds, unsigned int i)
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
		exit(free_all(data, NULL, 1));
}
