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

void	exec_redirections(t_data *data, t_command *cmd, int i)
{
	if (!is_there_chr(cmd->cmd, '>') && !is_there_chr(cmd->cmd, '<'))
		return ;
	cmd->input_redirection = redirection(cmd, '<', 0);
	cmd->output_redirection = redirection(cmd, '>', 0);
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '>' && !is_in_quotes(cmd->cmd, i))
			in_out_redirection(data, cmd, STDOUT_FILENO, i++);
		if (cmd->cmd[i] == '<' && !is_in_quotes(cmd->cmd, i))
			in_out_redirection(data, cmd, STDIN_FILENO, i++);
		i++;
	}
}
