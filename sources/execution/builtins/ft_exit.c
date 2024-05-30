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
	unsigned char	tmp;

	tmp = 0;
	(void)cmd;
	if (cmd->v_cmd[1])
		tmp = ft_atoi(cmd->v_cmd[1]);
	if (!tmp && cmd->v_cmd[1][0] != 0)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		set_return_value(1);
		return ;
	}
	if (cmd->v_cmd[1] && cmd->v_cmd[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		set_return_value(1);
		return ;
	}
	printf("exit\n");
	free_cmd_list(data->cmd_list);
	free_env(data->env_list, data->v_path);
	if (data->env && *data->env && **data->env)
		free_env(NULL, data->env);
	clear_history();
	ft_free(data->message);
	exit(tmp);
}
