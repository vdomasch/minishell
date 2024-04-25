/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:00:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/24 13:00:30 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_first(t_env *env)
{
	if (env)
	{
		while (env->prev)
			env = env->prev;
	}
	return (env);
}

t_env	*env_lstnew(t_env *prev)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->var = NULL;
	env->value = NULL;
	env->prev = prev;
	env->next = NULL;
	if (prev)
		prev->next = env;
	return (env);
}
