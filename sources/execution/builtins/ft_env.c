/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:48:09 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/13 11:48:11 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->var && env_list->value)
			printf("%s=%s\n", env_list->var, env_list->value);
		env_list = env_list->next;
	}
}
