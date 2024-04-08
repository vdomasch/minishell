/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:08:15 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/27 12:27:10 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *)dest;
	ptr2 = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (ptr2 < ptr1)
		while (n--)
			ptr1[n] = ptr2[n];
	else
		ptr1 = ft_memcpy(ptr1, ptr2, n);
	return (dest);
}
