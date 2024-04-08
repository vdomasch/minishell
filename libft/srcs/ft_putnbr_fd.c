/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:25:36 by vdomasch          #+#    #+#             */
/*   Updated: 2023/11/13 14:47:15 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		if (n > -10)
			write(fd, "-", 1);
		sign = -1;
	}
	if (n > 9 || n < -9)
		ft_putnbr_fd(n / 10, fd);
	n = n % 10 * sign + 48;
	write(fd, &n, 1);
}
