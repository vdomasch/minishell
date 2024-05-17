/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:39:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/12 11:54:53 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	exec_builtins(t_data *data, t_command *cmd)
{
	if (!*cmd->v_cmd)
		return (false);
	if (!ft_strncmp(data->cmd_list->v_cmd[0], "exit", 5))
	{
		printf("exit\n");
		if (cmd->v_cmd[1])
			exit(ft_atoi(cmd->v_cmd[1]));
		else
			exit(0);
	}
	else if (!ft_strncmp(cmd->v_cmd[0], "cd", 3))
		ft_cd(data, cmd->v_cmd);
	else if (!ft_strncmp(cmd->v_cmd[0], "export", 7))
		ft_export(data);
	else
		return (false);
	if (!ft_strncmp(cmd->v_cmd[0], "export", 7) && !cmd->v_cmd[1])
		return (false);
	return (true);
}

static bool	exec_builtins_child(t_data *data, t_command *command)
{
	if (!*command->v_cmd)
		return (false);
	if (!ft_strncmp(command->v_cmd[0], "exit", 5))
		;
	else if (!ft_strncmp(command->v_cmd[0], "cd", 3))
		;
	else if (!ft_strncmp(command->v_cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(command->v_cmd[0], "echo", 5))
		ft_echo(command->v_cmd);
	else if (!ft_strncmp(command->v_cmd[0], "env", 4))
		ft_env(data->env_list);
	else if (!ft_strncmp(command->v_cmd[0], "export", 7) && !command->v_cmd[1])
		ft_export_child(data->env);
	else if (!ft_strncmp(command->v_cmd[0], "unset", 6))
		;
	else
		return (false);
	return (true);
}

int	exec(t_data *data, t_command *cmd, int i)
{
	char	*path;

	if (exec_builtins_child(data, cmd))
		return (0);
	while (data->v_path[i])
	{
		if (*cmd->v_cmd)
		{
			path = ft_strjoin(data->v_path[i], "/");
			path = ft_strfreejoin(path, cmd->v_cmd[0]);
			execve(path, &cmd->v_cmd[0], data->env);
			ft_free(path);
		}
		i++;
	}
	return (1);
}
