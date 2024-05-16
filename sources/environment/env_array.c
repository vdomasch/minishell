/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:51:13 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/10 14:51:14 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**result;

	i = 0;
	while (env[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = NULL;
	i = 0;
	while (env[i])
	{
		result[i] = ft_strdup(env[i]);
		if (!result[i])
		{
			free_env(NULL, result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
