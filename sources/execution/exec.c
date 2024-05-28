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
	if (!cmd->v_cmd || !*cmd->v_cmd)
		return (false);
	if (*data->cmd_list->v_cmd
		&& !ft_strncmp(data->cmd_list->v_cmd[0], "exit", 5))
		ft_exit(data, cmd);
	if (!ft_strncmp(cmd->v_cmd[0], "cd", 3))
		ft_cd(data, cmd->v_cmd);
	else if (!ft_strncmp(cmd->v_cmd[0], "export", 7))
		ft_export(data);
	else if (!ft_strncmp(cmd->v_cmd[0], "unset", 6))
		ft_unset(data);
	else
		return (false);
	if (!ft_strncmp(cmd->v_cmd[0], "export", 7) && !cmd->v_cmd[1])
		return (false);
	return (true);
}

static bool	exec_builtins_child(t_data *data, t_command *command)
{
	if (!command->v_cmd || !*command->v_cmd)
		return (false);
	if (!ft_strncmp(command->v_cmd[0], "exit", 5))
		;
	else if (!ft_strncmp(command->v_cmd[0], "cd", 3))
		;
	else if (!ft_strncmp(command->v_cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(command->v_cmd[0], "echo", 5))
		ft_echo(data, command->v_cmd);
	else if (!ft_strncmp(command->v_cmd[0], "env", 4))
		ft_env(data->env_list);
	else if (!ft_strncmp(command->v_cmd[0], "export", 7) && !command->v_cmd[1])
		ft_export_child(data->env_list);
	else if (!ft_strncmp(command->v_cmd[0], "unset", 6))
		;
	else
		return (false);
	return (true);
}

char	*add_absolute_relative_path(t_command *cmd)
{
	char	*tmp;
	char	*abs_path;

	if (cmd->v_cmd[0][0] == '/')
	{
		tmp = ft_strdup(cmd->v_cmd[0]);
		if (!tmp)
			perror("Malloc failed: ");
		return (tmp);
	}
	if (ft_strncmp(cmd->v_cmd[0], "./", 2))
		return (NULL);
	abs_path = getcwd(NULL, 0);
	if (!abs_path)
	{
		perror("Error path: ");
		return (NULL);
	}
	tmp = ft_strjoin(abs_path, cmd->v_cmd[0] + 1);
	if (!tmp)
		perror("Malloc failed: ");
	free(abs_path);
	return (tmp);
}

int	exec(t_data *data, t_command *cmd, int i)
{
	char	*path;

	path = NULL;
	if (exec_builtins_child(data, cmd))
		return (0);
	path = add_absolute_relative_path(cmd);
	while ((data->v_path && data->v_path[i]) || path)
	{
		if (!cmd->v_cmd || !*cmd->v_cmd)
			return (2);
		if (!path && find_element_env_list(data->env_list, "PATH"))
		{
			path = ft_strjoin(data->v_path[i], "/");
			path = ft_strfreejoin(path, cmd->v_cmd[0]);
			if (!path)
				perror("Malloc failed: ");
		}
		execve(path, cmd->v_cmd, data->env);
		ft_free(path);
		path = NULL;
		i++;
	}
	return (1);
}
