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

static bool	echo_option(char *str)
{
	int	i;

	if (str && !*str)
		return (false);
	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

void	ft_echo(char **v_cmd)
{
	int	i;

	i = 1;
	if (!v_cmd || !*v_cmd)
		return ;
	while (echo_option(v_cmd[i]))
		i++;
	while (v_cmd[i])
	{
		printf("%s", v_cmd[i]);
		if (v_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!echo_option(v_cmd[1]))
		printf("\n");
}
