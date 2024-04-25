/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:16:05 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/17 18:01:56 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

static unsigned int	ft_strtrim_end(char const *s, char const *set, size_t len)
{
	size_t	i;
	size_t	count;
	size_t	outside;

	count = 0;
	outside = 1;
	while (len >= 0 && outside && s[len])
	{
		i = 0;
		while (set[i])
		{
			if (set[i] == s[len])
			{
				count++;
				break ;
			}
			i++;
			if (!set[i])
				outside = 0;
		}
		len--;
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
	end_count = ft_strtrim_end(s1, set, len);
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
