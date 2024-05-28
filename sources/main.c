/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:35:41 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/08 12:59:17 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_return_value;

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_command	command_list;

	(void)argc;
	(void)argv;
	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&data.cmd_list, 0, sizeof(t_command));
	data.cmd_list = &command_list;
	process_env(&data, env);
	if (!data.env)
	{
		perror("minishell: ");
		free_env(data.env_list, NULL);
		return (ENOMEM);
	}
	signal_set();
	ft_readline(&data);
	clear_history();
	free_env(data.env_list, data.v_path);
	if (data.env && *data.env && **data.env)
		free_env(NULL, data.env);
	return (0);
}
