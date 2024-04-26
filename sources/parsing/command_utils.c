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

#include "../../includes/minishell.h"

/*void	print_all(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("prev %p | actual %p ; !%s!| next %p\n",
			cmd->prev, cmd, cmd->cmd, cmd->next);
		i = 0;
		while (cmd->v_cmd[i])
		{
			printf("v_cmd = !%s!\n", cmd->v_cmd[i]);
			i++;
		}
		cmd = cmd->next;
	}
}*/

t_command	*cmd_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_command	*cmd_first(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	cmd = cmd_last(cmd);
	while (cmd)
	{
		tmp = cmd->prev;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->v_cmd)
		{
			i = 0;
			while (cmd->v_cmd[i])
				free(cmd->v_cmd[i++]);
			free(cmd->v_cmd);
		}
		if (cmd->prev)
			free(cmd);
		cmd = tmp;
	}
}

static void	cmd_new(t_command *prev)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return ;
	ft_memset(command, 0, sizeof(t_command));
	prev->next = command;
	command->prev = prev;
}

bool	create_cmd_list(t_data *data)
{
	t_command	*command;
	size_t		i;

	i = 0;
	command = data->cmd_list;
	while (i < data->nb_pipes)
	{
		cmd_new(command);
		if (command->next == NULL)
		{
			free_cmd_list(command);
			return (false);
		}
		command = command->next;
		i++;
	}
	return (true);
}
