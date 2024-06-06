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
	*start = i;
	while (cmd[i])
	{
		if (ft_isspace(cmd[i]) && !is_in_quotes(cmd, i))
			break ;
		i++;
	}
	return (i - *start);
}

static int count_quotes(const char *str)
{
	int i;
	int quotes;
	int count;

	i = 0;
	quotes = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quotes == 0)
		{
			if (str[i] == '\'')
				quotes--;
			else
				quotes++;
			count++;
		}
		else if (((str[i] == '\'' && quotes == -1) || (str[i] == '"' && quotes == 1)))
		{
			quotes = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static char *copy_without_quotes(char *str)
{
	unsigned int	i;
	unsigned int	j;
	int				quotes;
	char			*result;

	result = malloc(sizeof(char) * (ft_strlen(str) - count_quotes(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quotes = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quotes == 0)
		{
			if (str[i] == '\'')
				quotes--;
			else
				quotes++;
		}
		else if (((str[i] == '\'' && quotes == -1) || (str[i] == '"' && quotes == 1)))
			quotes = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
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
	str = copy_without_quotes(str);
	return (str);
}

char	*next_redirection_name(t_command *cmd, int i)
{
	int		len;
	char	*redirection;

	while (cmd->cmd[i] == '<' || cmd->cmd[i] == '>')
		i++;
	while (cmd->cmd[i] && ft_isspace(cmd->cmd[i]))
		i++;
	len = 0;
	while (cmd->cmd[i + len] && (!ft_isspace(cmd->cmd[i + len])
			|| is_in_quotes(cmd->cmd, i + len)))
		len++;
	redirection = malloc(sizeof(char) * (len + 1));
	if (!redirection)
		return (NULL);
	redirection[len] = '\0';
	while (--len >= 0)
		redirection[len] = cmd->cmd[i + len];
	redirection = copy_without_quotes(redirection);
	return (redirection);
}

bool	check_last_redirection(t_command *command, char *redirection, int i)
{
	char *pathname;

	pathname = next_redirection_name(command, i);
	if (!ft_strncmp(redirection, pathname, ft_strlen(pathname) + 1))
	{
		while (ft_isspace(command->cmd[i]))
			i++;
		i += ft_strlen(pathname);
		while (command->cmd[++i])
			if ((command->cmd[i] == '<' || command->cmd[i] == '>') && !is_in_quotes(command->cmd, i))
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
			if (check_last_redirection(command, command->input_redirection, i) && !command->next)
				return (1);
		}
		i++;
	}
	return (0);
}
