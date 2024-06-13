/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:46:01 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/09 11:46:03 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_command_valid(const char *message)
{
	if (are_quotes_closed(message))
		ft_putstr_fd(ERR_QUOTE_NOT_CLOSED, 2);
	else if (is_invalid_char_in_quote(message))
		ft_putstr_fd(ERR_SPECIAL_CHAR, 2);
	else if (is_starting_by_pipe(message))
		ft_putstr_fd(ERR_PIPE_START, 2);
	else if (is_ended_by_pipe(message))
		ft_putstr_fd(ERR_PIPE_END, 2);
	else if (is_empty_pipe(message))
		ft_putstr_fd(ERR_EMPTY_PIPE, 2);
	else if (!is_redirection_valid(message))
		ft_putstr_fd(ERR_INVALID_REDIRECTION, 2);
	else
		return (true);
	ft_free((char *)message);
	set_return_value(2);
	return (false);
}

char	*cut_commands(const char *message, int letter, int j)
{
	static int	i = 0;
	char		*cmd;

	if (message[i] == '|')
		i++;
	j = i;
	while (message[i])
	{
		if (message[i] == '|' && !is_in_quotes(message, i))
			break ;
		i++;
	}
	cmd = malloc(sizeof(char) * (i - j + 1));
	if (!cmd)
		return (NULL);
	while (j < i)
		cmd[letter++] = message[j++];
	cmd[letter] = '\0';
	if (!message[i])
		i = 0;
	return (cmd);
}

bool	split_command(t_data *data, t_command *command)
{
	char	*cmd_clean;

	while (command)
	{
		cmd_clean = clean_command(command->cmd);
		if (!cmd_clean)
		{
			ft_free(data->message);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command->v_cmd = split_arguments(cmd_clean, " \n\r\t\v\f");
		if (!command->v_cmd)
		{
			ft_free(data->message);
			ft_free(cmd_clean);
			free_cmd_list(command);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
		ft_free(cmd_clean);
	}
	return (true);
}

bool	standardize_command(t_data *data, char *message, t_command *command)
{
	command = data->cmd_list;
	data->message = replace_variables(data, message, data->env_list);
	if (!data->message)
		return (false);
	if (!is_command_valid(data->message))
		return (false);
	data->nb_pipes = count_pipes(data->message);
	if (!create_cmd_list(data))
		return (false);
	while (command)
	{
		command->cmd = ft_free_strtrim(cut_commands(data->message, 0, 0),
				" \n\r\t\v\f");
		if (!command->cmd)
		{
			ft_free(data->message);
			free_cmd_list(data->cmd_list);
			perror("minishell: malloc: ");
			return (false);
		}
		command = command->next;
	}
	if (!split_command(data, data->cmd_list))
		return (false);
	return (true);
}

int	process_message(t_data *data, char *message)
{
	data->message = message;
	ft_memset(data->cmd_list, 0, sizeof(t_command));
	if (!standardize_command(data, message, NULL))
		return (4);
	pipes_commands(data, data->cmd_list, 0);
	if (access(".tmp.txt", 1))
		unlink(".tmp.txt");
	free_cmd_list(data->cmd_list);
	ft_free(data->message);
	return (0);
}
