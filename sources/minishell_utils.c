/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:32:19 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/25 14:32:21 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_free_strtrim(char *s1, const char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strtrim(s1, s2);
	free(s1);
	return (result);
}

bool	str_is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	str_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}