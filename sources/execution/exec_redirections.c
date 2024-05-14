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

bool	is_there_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_in_quotes(str, i))
			return (true);
		i++;
	}
	return (false);
}

int	last_redirection_size(char *cmd, char c, int *start)
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
	if (cmd[i] == '\'' || cmd[i] == '"')
		i++;
	*start = i;
	while (cmd[i])
	{
		if (ft_isspace(cmd[i]) && !is_in_quotes(cmd, i))
			break ;
		i++;
	}
	if (cmd[i] == '\'' || cmd[i] == '"')
		i--;
	return (i - *start);
}

char	*redirection(t_command *cmd, char input_token)
{
	char	*str;
	int		start;
	int		i;

	if (!is_there_chr(cmd->cmd, input_token))
		return (NULL);
	str = malloc(sizeof(char)
			* (last_redirection_size(cmd->cmd, input_token, &start) + 1));
	if (!str)
		return (NULL);
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
	return (str);
}

char	*next_redirection_name(t_command *cmd, int i)
{
	int		len;
	char	*redirection;

	while (cmd->cmd[i] && ft_isspace(cmd->cmd[i]))
		i++;
	if (cmd->cmd[i] == '\'' || cmd->cmd[i] == '"')
		i++;
	len = 0;
	while (cmd->cmd[i + len] && (!ft_isspace(cmd->cmd[i + len]) || is_in_quotes(cmd->cmd, i + len)))
		len++;
	if (cmd->cmd[i + len - 1] == '\'' || cmd->cmd[i + len - 1] == '"')
		len--;
	redirection = malloc(sizeof(char) * (len + 1));
	if (!redirection)
		return (NULL);
	redirection[len] = '\0';
	while (--len >= 0)
	{
		redirection[len] = cmd->cmd[i + len];
	}
	return (redirection);
}

void	exec_redirections(t_command *command, unsigned int nb_pipes,
						  int *pipe_fds, unsigned int pipe_id)
{
	int	i;

	i = 0;
	if (!is_there_chr(command->cmd, '>') && !is_there_chr(command->cmd, '<'))
		return ;
	command->input_redirection = redirection(command, '<');
	command->output_redirection = redirection(command, '>');
	while (command->cmd[i])
	{
		if (pipe_fds && pipe_id != 2 * nb_pipes && command->cmd[i] == '>')
			in_out_redirection(command, pipe_fds[pipe_id + 1], i++);
		else if (command->cmd[i] == '>')
			in_out_redirection(command, STDOUT_FILENO, i++);
		else if (pipe_fds && pipe_id != 2 * nb_pipes && command->cmd[i] == '<')
			in_out_redirection(command, pipe_fds[pipe_id], i++);
		else if (command->cmd[i] == '<')
			in_out_redirection(command, STDIN_FILENO, i++);
		i++;
	}
}
