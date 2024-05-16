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

#include "../../includes/minishell.h"

bool	is_command_valid(const char *message)
{
	if (are_quotes_closed(message))
		printf(ERR_QUOTE_NOT_CLOSED);
	else if (is_invalid_char_in_quote(message))
		printf(ERR_SPECIAL_CHAR);
	else if (is_starting_by_pipe(message))
		printf(ERR_PIPE_START);
	else if (is_ended_by_pipe(message))
		printf(ERR_PIPE_END);
	else if (is_empty_pipe(message))
		printf(ERR_EMPTY_PIPE);
	else if (!is_redirection_valid(message))
		printf(ERR_INVALID_REDIRECTION);
	else
		return (true);
	free((char *)message);
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
			free(data->message);
			free_cmd_list(command);
			return (false);
		}
		command->v_cmd = split_arguments(cmd_clean, " \n\r\t\v\f");
		if (!command->v_cmd)
		{
			free(data->message);
			free(cmd_clean);
			free_cmd_list(command);
			return (false);
		}
		command = command->next;
		free(cmd_clean);
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
			free(data->message);
			free_cmd_list(data->cmd_list);
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
	if (data->nb_pipes > 50)
		printf("minishell: too many pipes used\n");
	else
		pipes_commands(data, data->cmd_list, 0);
	free_cmd_list(data->cmd_list);
	free(data->message);
	return (0);
}
