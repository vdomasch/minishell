/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:46:01 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/09 11:46:03 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int process_message(char *message)
{
	char **str;
	int i = 0;

	if (!ft_strncmp(message, "exit", 5))
	{
		printf("%s\n", message);
		return (1);
	}
	else if (message[0])
	{
		printf("%s: command not found\n", message);
		//return (2);
	}
	return (0);
}