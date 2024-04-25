/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:30:21 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/18 16:30:23 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_pipes(const char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes(str, i))
			count++;
		i++;
	}
	return (count);
}

bool	is_empty_pipe(const char *str)
{
	int		i;
	bool	empty;

	i = 0;
	empty = false;
	while (str[i] && empty == false)
	{
		while (str[i] && (str[i] != '|' || (str[i] == '|'
					&& is_in_quotes(str, i))))
			i++;
		if (!str[i])
			return (false);
		if (str[i + 1] == '|')
			return (true);
		i++;
		empty = true;
		while (str[i] && (str[i] != '|' || (str[i] == '|'
					&& is_in_quotes(str, i))))
		{
			if ((!ft_strchr("|<>", str[i]) && !ft_isspace(str[i])))
				empty = false;
			i++;
		}
	}
	return (empty);
}

bool	is_ended_by_pipe(const char *str)
{
	int		i;
	int		j;
	bool	pipe;

	i = 0;
	j = -1;
	pipe = true;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes(str, i))
			j = i + 1;
		i++;
	}
	while (j > -1 && str[j] && pipe == true)
	{
		if (!ft_isspace(str[j]))
			pipe = false;
		j++;
	}
	if (j == -1)
		pipe = false;
	return (pipe);
}

bool	is_starting_by_pipe(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] != '|' && !ft_isspace(str[i]))
			return (false);
		i++;
	}
	if (!str[i])
		return (false);
	return (true);
}
