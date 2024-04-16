/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multisplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:45:57 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/09 12:46:24 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static bool	char_sym(const char s, const char *charset)
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

static unsigned int	count_word(const char *s, const char *charset)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	i = 0;
	while (*s)
	{
		while (*s && char_sym(*s, charset))
			s++;
		if (*s)
			count++;
		while (*s && !char_sym(*s, charset))
			s++;
	}
	return (count);
}

static char	*alloc(const char *s, const char *set, unsigned int current_word)
{
	char			*word;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	i = 0;
	while (current_word--)
	{
		while (s[i] && char_sym(s[i], set))
			i++;
		start = i;
		while (s[i] && !char_sym(s[i], set))
			i++;
	}
	end = i;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**split(const char *s, char *set)
{
	char				**array;
	unsigned int		nb_word;
	unsigned int		current_word;

	current_word = 0;
	nb_word = count_word(s, set);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc(s, set, current_word);
		if (array[current_word - 1] == NULL)
		{
			while (current_word--)
				free(array[current_word]);
			free(array);
			return (NULL);
		}
	}
	array[current_word - 1] = NULL;
	return (array);
}
