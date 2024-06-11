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

bool	check_last_redirection(char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quotes(str, i))
			return (false);
		i++;
	}
	return (true);
}

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

char	*redirection(t_command *cmd, char input_token, int i)
{
	char	*str;
	int		start;

	if (!is_there_chr(cmd->cmd, input_token))
		return (NULL);
	str = malloc(sizeof(char)
			* (last_redirection_size(cmd->cmd, input_token, &start) + 1));
	if (!str)
	{
		perror("minishell: malloc: ");
		return (NULL);
	}
	while (cmd->cmd[start])
	{
		if (ft_isspace(cmd->cmd[start]) && !is_in_quotes(cmd->cmd, start))
			break ;
		str[i] = cmd->cmd[start];
		start++;
		i++;
	}
	str[i] = '\0';
	if (is_there_chr(str, '"') || is_there_chr(str, '\''))
		str = str_without_quotes(str);
	return (str);
}

static bool	check_last_redir_name(t_command *command, char *redirection,
								char c, int i)
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
		free(pathname);
		if (is_there_chr(command->cmd + i + 1, c))
			return (false);
		while (ft_isspace(command->cmd[i]))
			i++;
		i += ft_strlen(redirection) - 1;
		while (command->cmd[++i])
			if ((command->cmd[i] == '<' || command->cmd[i] == '>')
				&& !is_in_quotes(command->cmd, i))
				return (false);
		return (true);
	}
	free(pathname);
	return (false);
}

int	exec_redirections(t_data *data, t_command *cmd, int i)
{
	if (!is_there_chr(cmd->cmd, '>') && !is_there_chr(cmd->cmd, '<'))
		return (0);
	cmd->input_redirection = redirection(cmd, '<', 0);
	cmd->output_redirection = redirection(cmd, '>', 0);
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '>' && !is_in_quotes(cmd->cmd, i))
		{
			in_out_redirection(data, cmd, STDOUT_FILENO, i++);
			if (check_last_redir_name(cmd,
					cmd->output_redirection, '>', i) && !cmd->prev)
				return (1);
		}
		if (cmd->cmd[i] == '<' && !is_in_quotes(cmd->cmd, i))
		{
			in_out_redirection(data, cmd, STDIN_FILENO, i++);
			if (check_last_redir_name(cmd, cmd->input_redirection, '<', i)
				&& !cmd->next && check_last_redirection(cmd->cmd + i + 1, '>'))
				return (1);
		}
		i++;
	}
	return (0);
}
