/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:51:31 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/17 15:51:37 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(t_data *data, t_command *cmd)
{
	int	tmp;

	tmp = 0;
	if (cmd->v_cmd[1])
		tmp = ft_atoi(cmd->v_cmd[1]);
	(void)data;
	printf("exit\n");
	free_cmd_list(data->cmd_list);
	free_env(data->env_list, data->v_path);
	free_env(NULL, data->env);
	clear_history();
	ft_free(data->message);
	exit(tmp);
}
