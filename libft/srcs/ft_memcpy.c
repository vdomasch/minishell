/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:42 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/09 11:53:21 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	if (src == NULL && dest == NULL)
		return (dest);
	ptr1 = (char *)dest;
	ptr2 = (char *)src;
	while (n--)
		*(ptr1++) = *(ptr2++);
	return (dest);
}
