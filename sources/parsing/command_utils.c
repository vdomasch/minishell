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

t_command	*cmd_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
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
		ft_free(cmd->cmd);
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
		ft_free(cmd->input_redirection);
		ft_free(cmd->output_redirection);
		if (cmd->v_cmd)
		{
			i = 0;
			while (cmd->v_cmd[i])
				ft_free(cmd->v_cmd[i++]);
			ft_free(cmd->v_cmd);
		}
		if (cmd->prev)
			ft_free(cmd);
		cmd = tmp;
	}
}

static void	cmd_new(t_command *prev)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
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
		if (!command->next)
		{
			ft_free(data->message);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
		i++;
	}
	return (true);
}
