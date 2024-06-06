/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:57:46 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/08 13:57:50 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	last_redirection_size(char *cmd, char c, int *start)
{
	int	i;

	i = (int)ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == c && !is_in_quotes(cmd, i))
			break ;
		i--;
	}
	if (i == -1)
		return (0);
	while (cmd[i] && ft_isspace(cmd[++i]))
		;
	*start = i;
	while (cmd[i])
	{
		if (ft_isspace(cmd[i]) && !is_in_quotes(cmd, i))
			break ;
		i++;
	}
	return (i - *start);
}

static char	*redirection(t_command *cmd, char input_token)
{
	char	*str;
	int		start;
	int		i;

	if (!is_there_chr(cmd->cmd, input_token))
		return (NULL);
	str = malloc(sizeof(char)
			* (last_redirection_size(cmd->cmd, input_token, &start) + 1));
	if (!str)
	{
		perror("minishell: malloc: ");
		return (NULL);
	}
	i = 0;
	while (cmd->cmd[start])
	{
		if (ft_isspace(cmd->cmd[start]) && !is_in_quotes(cmd->cmd, start))
			break ;
		str[i] = cmd->cmd[start];
		start++;
		i++;
	}
	str[i] = '\0';
	str = str_without_quotes(str, 0, 0, 0);
	return (str);
}

static bool	check_last_redirection(t_command *command, char *redirection, int i)
{
	char	*pathname;

	pathname = next_redirection_name(command, i);
	if (!pathname)
	{
		perror("minishell: malloc: ");
		return (false);
	}
	if (!ft_strncmp(redirection, pathname, ft_strlen(pathname) + 1))
	{
		while (ft_isspace(command->cmd[i]))
			i++;
		i += ft_strlen(pathname);
		while (command->cmd[++i])
			if ((command->cmd[i] == '<' || command->cmd[i] == '>')
				&& !is_in_quotes(command->cmd, i))
				return (false);
		free(pathname);
		return (true);
	}
	free(pathname);
	return (false);
}

int	exec_redirections(t_data *data, t_command *command)
{
	int	i;

	i = 0;
	if (!is_there_chr(command->cmd, '>') && !is_there_chr(command->cmd, '<'))
		return (0);
	command->input_redirection = redirection(command, '<');
	command->output_redirection = redirection(command, '>');
	while (command->cmd[i])
	{
		if (command->cmd[i] == '>' && !is_in_quotes(command->cmd, i))
		{
			in_out_redirection(data, command, STDOUT_FILENO, i++);
			if (check_last_redirection(command, command->output_redirection, i))
				return (1);
		}
		if (command->cmd[i] == '<' && !is_in_quotes(command->cmd, i))
		{
			in_out_redirection(data, command, STDIN_FILENO, i++);
			if (check_last_redirection(command, command->input_redirection, i)
				&& !command->next)
				return (1);
		}
		i++;
	}
	return (0);
}
