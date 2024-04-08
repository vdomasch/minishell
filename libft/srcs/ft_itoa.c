/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:39:23 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/17 18:02:37 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	number_len(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		neg;
	char	*number;

	neg = 1;
	if (n < 0)
		neg = -1;
	len = number_len(n);
	number = (char *)malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	number = number + len;
	*number = '\0';
	if (n == 0)
		*(--number) = (n % 10) * neg + 48;
	while (n != 0)
	{
		*(--number) = (n % 10) * neg + 48;
		n = n / 10;
	}
	if (neg == -1)
		*(--number) = '-';
	return (number);
}
