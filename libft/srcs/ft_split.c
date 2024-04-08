/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:57:47 by vdomasch          #+#    #+#             */
/*   Updated: 2024/02/23 18:42:21 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	*alloc_word(const char *s, char c, size_t current_word)
{
	char	*word;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	while (current_word--)
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
	}
	end = i;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char		**array;
	size_t		nb_word;
	size_t		current_word;

	current_word = 0;
	nb_word = count_word(s, c);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc_word(s, c, current_word);
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
