/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:56:58 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/08 13:13:04 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

//////////////////////////////// ft_strtrim ////////////////////////////

static unsigned int	ft_strtrim_start(char const *s, char const *set)
{
	size_t	i;
	size_t	count;
	size_t	outside;

	count = 0;
	outside = 1;
	while (*s && outside)
	{
		i = 0;
		while (set[i])
		{
			if (set[i] == *s)
			{
				count++;
				break ;
			}
			i++;
			if (!set[i])
				outside = 0;
		}
		s++;
	}
	if (!(*s))
		count = 0;
	return (count);
}

static unsigned int	ft_strtrim_end(char const *s, char const *set)
{
	size_t	i;
	size_t	count;
	size_t	outside;

	count = 0;
	outside = 1;
	while (*s && outside)
	{
		i = 0;
		while (set[i])
		{
			if (set[i] == *s)
			{
				count++;
				break ;
			}
			i++;
			if (!set[i])
				outside = 0;
		}
		s--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		i;
	size_t		len;
	size_t		start_count;
	size_t		end_count;

	len = ft_strlen(s1);
	start_count = ft_strtrim_start(s1, set);
	end_count = ft_strtrim_end(s1 + len - 1, set);
	s1 = s1 + start_count;
	len = len - (start_count + end_count);
	i = len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i--)
		*(str++) = *(s1++);
	*str = '\0';
	return (str - len);
}

///////////////////////////////////////////////////////////////////

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

///////////////////////////ft_split////////////////////////////////////

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

/////////////////////////////////////////////////////////////////