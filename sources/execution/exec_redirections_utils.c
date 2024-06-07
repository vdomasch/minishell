/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirecrtion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:28:25 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/06 16:28:27 by vdomasch         ###   ########.fr       */
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

char	*next_redirection_name(t_command *cmd, int i)
{
	int		len;
	char	*redirection;

	while (cmd->cmd[i] == '<' || cmd->cmd[i] == '>' || ft_isspace(cmd->cmd[i]))
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
	if (is_there_chr(redirection, '\'') || is_there_chr(redirection, '"'))
		redirection = str_without_quotes(redirection);
	return (redirection);
}

static int	count_quotes(const char *str)
{
	int	i;
	int	qts;
	int	count;

	i = 0;
	qts = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && qts == 0)
		{
			if (str[i] == '\'')
				qts--;
			else
				qts++;
			count++;
		}
		else if ((str[i] == '\'' && qts == -1) || (str[i] == '"' && qts == 1))
		{
			qts = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static void	copy_quoteless(char *result, char *str)
{
	unsigned int	i;
	unsigned int	j;
	int				qts;

	i = 0;
	j = 0;
	qts = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && qts == 0)
		{
			qts++;
			if (str[i] == '\'')
				qts -= 2;
		}
		else if ((str[i] == '\'' && qts == -1) || (str[i] == '"' && qts == 1))
			qts = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
}

char	*str_without_quotes(char *str)
{
	char			*result;

	result = malloc(sizeof(char) * (ft_strlen(str) - count_quotes(str) + 1));
	if (!result)
	{
		perror("minishell: malloc: ");
		free(str);
		return (NULL);
	}
	copy_quoteless(result, str);
	free(str);
	return (result);
}
