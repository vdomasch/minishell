/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:00:15 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/18 17:00:16 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_command *cmd)
{
	while (cmd)
	{
		printf("prev %p | actual %p ; !%s!| next %p\n", cmd->prev, cmd, cmd->cmd, cmd->next);
		cmd = cmd->next;
	}
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;

	cmd = cmd_last(cmd);
	while (cmd->prev)
	{
		tmp = cmd->prev;
		if (cmd->cmd)
			free(cmd->cmd);
		free(cmd);
		cmd = tmp;
	}
	free(cmd->cmd);
}

t_command	*cmd_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_new(t_command *prev)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return ;
	ft_memset(command, 0, sizeof(t_command));
	prev->next = command;
	command->prev = prev;
}
