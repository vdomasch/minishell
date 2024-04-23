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

char	*ft_free_strtrim(char *s1, const char *s2)
{
	char *result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strtrim(s1, s2);
	free(s1);
	return (result);
}

bool	create_cmd_list(t_data *data)
{
	t_command	*command;
	size_t 		i;

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

bool	is_command_valid(const char *message)
{
	if (are_quotes_closed(message) == 1)
		printf("\nError, quote isn't closed!\n");
	else if (is_invalid_char_in_quote(message) == 1)
		printf("\nError, special character not in quote!\n");
	else if (is_starting_by_pipe(message) == 1)
		printf("\nError, is starting by pipe!\n");
	else if (is_ended_by_pipe(message) == 1)
		printf("\nError, ended by pipes!\n");
	else if (is_empty_pipe(message))
		printf("\nError, empty pipe!\n");
	else
		return (true);
	return (false);
}

char	*cut_commands(const char *message)
{
	static int	i = 0;
	int			j;
	char		*cmd;
	int 		letter;

	if (message[i] == '|')
		i++;
	j = i;
	letter = 0;
	while (message[i])
	{
		if (message[i] == '|' && !is_in_quotes(message, i))
			break ;
		i++;
	}
	cmd = malloc(sizeof(char) * (i - j + 1));
	if (!cmd)
	{
		printf("Error, malloc failed!\n");
		return (NULL);
	}
	while (j < i)
		cmd[letter++] = message[j++];
	cmd[letter] = '\0';
	if (!message[i])
		i = 0;
	return (cmd);
}

int 	size_without_redirection(char *cmd, int *i, int res)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '>' || cmd[*i] == '<')
			break;
		*i += 1;
	}
	if (!cmd[*i])
		return (0);
	res = *i;
	*i += 1;
	if (cmd[*i] == '>' || cmd[*i] == '<')
		*i += 1;
	while (cmd[*i] && ft_isspace(cmd[*i]))
		*i += 1;
	while (cmd[*i])
	{
		if (ft_isspace(cmd[*i]) && !is_in_quotes(cmd, *i))
			break ;
		*i += 1;
	}
	res = *i - res;
	return (res);
}

char	*clean_command(char *cmd)
{
	char	*result;
	int 	len;
	int		i;

	i = 0;
	len = 0;
	while (cmd[i])
		len += size_without_redirection(cmd, &i, len);
	result = cmd;
	return (result);
}

bool	split_command(t_command *command)
{
	char	*cmd_clean;

	while (command)
	{
		cmd_clean = clean_command(command->cmd);
		if (!cmd_clean)
		{
			free_cmd_list(command);
			return (false);
		}
		/*command->v_cmd = split_arguments(cmd_clean, " \n\r\t\v\f");
		if (!command->v_cmd)
		{
			free_cmd_list(command);
			return (false);
		}*/




		command = command->next;
	}
	return (true);
}

bool	standardize_command(t_data *data, const char *message)
{
	t_command *command;

	command = data->cmd_list;
	if (!is_command_valid(message))
		return (false);
	data->nb_pipes = count_pipes(message);
	if (!create_cmd_list(data))
		return (false);
	while (command)
	{
		command->cmd = ft_free_strtrim(cut_commands(message), " \n\r\t\v\f");
		if (!command->cmd)
			return (false);
		command = command->next;
	}
	if (!split_command(data->cmd_list))
		return (false);
	return (true);
}

int process_message(t_data *data, const char *message)
{
	ft_memset(data->cmd_list, 0, sizeof(t_command));
	if (!standardize_command(data, message))
		return (4);
	free_cmd_list(data->cmd_list);
	if (!ft_strncmp(message, "exit", 5))
	{
		printf("%s\n", message);
		exit (0);
	}
	else if (message[0])
	{
		printf("%s: command not found\n", message);
		return (2);
	}
	return (0);
}
