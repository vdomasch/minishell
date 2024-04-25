/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:21:15 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/25 14:21:17 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	size_redirection(char *cmd, int *i, int res)
{
	while (cmd[*i])
	{
		if ((cmd[*i] == '>' || cmd[*i] == '<') && !is_in_quotes(cmd, *i))
			break ;
		*i += 1;
	}
	if (!cmd[*i])
		return (0);
	res = *i;
	*i += 1;
	if ((cmd[*i] == '>' || cmd[*i] == '<') && !is_in_quotes(cmd, *i))
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

static void	copy_without_redirections(char *cmd, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && !is_in_quotes(cmd, i))
			size_redirection(cmd, &i, 0);
		if (!cmd[i])
			break ;
		result[j++] = cmd[i++];
	}
	result[j] = '\0';
}

char	*clean_command(char *cmd)
{
	char	*result;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (cmd[i])
		len += size_redirection(cmd, &i, 0);
	result = malloc(sizeof(char) * (ft_strlen(cmd) - len + 1));
	if (!result)
		return (NULL);
	copy_without_redirections(cmd, result);
	return (result);
}
