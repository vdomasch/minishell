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

bool	exec_builtins(t_data *data)
{
	if (!ft_strncmp(data->cmd_list->v_cmd[0], "exit", 5))
		printf("exit\n");
	else if (!ft_strncmp(data->cmd_list->v_cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(data->cmd_list->v_cmd[0], "echo", 5))
		ft_echo(data->cmd_list->v_cmd);
	//else if (!ft_strncmp(data->cmd_list->v_cmd[0], "export", 7))
	//	ft_export(data);
	else
		return (false);
	return (true);
}

int	exec(t_data *data, t_command *cmd, int i)
{
	char	*path;

	//if (exec_builtins(data))
	//	return (0);
	while (data->v_path[i])
	{
		path = ft_strjoin(data->v_path[i], "/");
		path = ft_strfreejoin(path, cmd->v_cmd[0]);
		execve(path, &cmd->v_cmd[0], data->env);
		free(path);
		i++;
	}
	return (1);
}
