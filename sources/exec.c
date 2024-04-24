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

#include "../includes/minishell.h"

int	exec_builtins(char **v_cmd)
{
	if (!ft_strncmp(v_cmd[0], "exit", 5))
		exit(0);
	if (!ft_strncmp(v_cmd[0], "export", 6))
		return (1);
	//list all builtins
	return (0);
}

int	exec(t_data *data)
{
	char	*path;
	int		pc_id;
	int		status;
	int		i;

	if (exec_builtins(data->cmd_list->v_cmd))
		return (0);
	pc_id = fork();
	status = 0;
	i = 0;
	if (pc_id == 0)
	{
		while (data->v_path[i])
		{
			path = ft_strjoin(data->v_path[i], "/");
			path = ft_strfreejoin(path, data->cmd_list->v_cmd[0]);
			execve(path, &data->cmd_list->v_cmd[0], NULL);
			free(path);
			i++;
		}
		return (1);
	}
	if (waitpid(pc_id, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
	{
		printf("Process finished with success\n");
		return (0);
	}
	else
		printf("Failure\n");
	return (1);
}
