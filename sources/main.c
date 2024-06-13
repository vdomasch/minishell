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

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_command	command_list;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&data.cmd_list, 0, sizeof(t_command));
	process_env(&data, env);
	data.cmd_list = &command_list;
	data.stdin = dup(STDIN_FILENO);
	if (!data.env)
	{
		perror("minishell: ");
		free_env(data.env_list, NULL);
		close (data.stdin);
		return (ENOMEM);
	}
	ft_readline(&data);
	rl_clear_history();
	close (data.stdin);
	free_env(data.env_list, data.v_path);
	if (data.env && *data.env && **data.env)
		free_env(NULL, data.env);
	return (0);
}
