/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:13 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/10 16:14:00 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	if (size == 0)
		return (len_src);
	if (len_dst >= size)
		return (len_src + size);
	size = size - len_dst;
	i = len_dst;
	j = 0;
	while (src[j] && size > 1)
	{
		dst[i++] = src[j++];
		size--;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
