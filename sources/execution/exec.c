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

int	exec_builtins(char **v_cmd)
{
	if (!ft_strncmp(v_cmd[0], "exit", 5))
	{
		printf("exit");
		exit(0);
	}
	if (!ft_strncmp(v_cmd[0], "export", 6))
		return (1);
	return (0);
}

int	exec(t_data *data, int pc_id, int status, int i)
{
	char	*path;

	if (exec_builtins(data->cmd_list->v_cmd))
		return (0);
	pc_id = fork();
	if (pc_id == 0)
	{
		while (data->v_path[i])
		{
			path = ft_strjoin(data->v_path[i], "/");
			path = ft_strfreejoin(path, data->cmd_list->v_cmd[0]);
			execve(path, &data->cmd_list->v_cmd[0], data->env);
			free(path);
			i++;
		}
		exit(1);
	}
	if (waitpid(pc_id, &status, 0) == -1)
		return (3);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (1);
	return (0);
}
