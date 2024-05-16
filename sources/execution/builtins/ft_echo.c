/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:35:05 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/07 17:35:06 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(char **v_cmd)
{
	int	i;

	i = 1;
	if (!ft_strncmp(v_cmd[1], "-n", 3))
		i++;
	while (v_cmd[i])
	{
		printf("%s", v_cmd[i]);
		if (v_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(v_cmd[1], "-n", 3))
		printf("\n");
}
