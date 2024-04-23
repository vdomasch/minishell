/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:29:44 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/18 16:29:46 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_in_quotes(const char *str, int j)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (i <= j)
	{
		if ((str[i] == '"' && quotes == 0) || (str[i] == '\'' && quotes < 0))
			quotes++;
		else if ((str[i] == '\'' && quotes == 0) || (str[i] == '"'
				&& quotes > 0))
			quotes--;
		i++;
	}
	if (quotes == 0)
		return (false);
	return (true);
}

bool	is_invalid_char_in_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_strchr("~`#&*()\\[]{};?!", str[i]) && !is_in_quotes(str, i)))
			return (true);
		i++;
	}
	return (false);
}

bool	is_quote_closed(const char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if ((str[i] == '"' && quotes == 0) || (str[i] == '\'' && quotes < 0))
			quotes++;
		else if ((str[i] == '\'' && quotes == 0)
			|| (str[i] == '"' && quotes > 0))
			quotes--;
		i++;
	}
	if (quotes == 0)
		return (false);
	return (true);
}
