/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:48:12 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/06 16:48:14 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	char_sym(const char s, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i++] == s)
			return (1);
	}
	return (0);
}

void	copy_without_quotes(char *word, const char *s, unsigned int start,
							unsigned int end)
{
	int				quotes;
	unsigned int	i;

	i = 0;
	quotes = 0;
	while (start <= end)
	{
		if ((s[start] == '\'' || s[start] == '"') && quotes == 0)
		{
			if (s[start] == '\'')
				quotes--;
			else
				quotes++;
		}
		else if (((s[start] == '\'' && quotes == -1)
				|| (s[start] == '"' && quotes == 1)))
			quotes = 0;
		else
			word[i++] = s[start];
		start++;
	}
	word[i - 1] = '\0';
}
