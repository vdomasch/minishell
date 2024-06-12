/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:11:12 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/29 15:11:17 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_more_than_two_redirections(const char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0;
		while (str[i] && (str[i] == '<' || str[i] == '>' || ft_isspace(str[i]))
			&& !is_in_quotes(str, i))
		{
			if ((str[i] == '<' || str[i] == '>') && !is_in_quotes(str, i))
				count++;
			i++;
		}
		if (count > 2)
			return (true);
		if (str[i])
			i++;
	}
	return (false);
}

bool	is_redirection_followed_by_pipe(const char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quotes(str, i))
		{
			j = i - 1;
			while (str[j] && str[j] != '|' && !is_in_quotes(str, j))
			{
				if ((str[j] == '<' || str[j] == '>') && !is_in_quotes(str, j))
					return (true);
				if (!ft_isspace(str[j]))
					break ;
				j--;
			}
		}
		i++;
	}
	return (false);
}

bool	is_ending_by_redirection(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i >= 0 && str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (true);
		if (!ft_isspace(str[i]))
			return (false);
		i--;
	}
	return (false);
}

bool	is_redirection_valid(const char *str)
{
	if (is_ending_by_redirection(str))
		return (false);
	if (is_redirection_followed_by_pipe(str))
		return (false);
	if (is_more_than_two_redirections(str))
		return (false);
	return (true);
}
