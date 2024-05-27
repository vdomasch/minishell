/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:42:54 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/15 13:42:55 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_env	*find_smallest_in_alphabetical_order(t_env *env)
{
	t_env	*list;
	t_env	*smallest;

	list = env;
	smallest = list;
	while (list)
	{
		if (ft_strncmp(list->var, smallest->var, ft_strlen(smallest->var)) < 0)
			smallest = list;
		list = list->next;
	}
	return (smallest);
}

static t_env	*find_highest_in_alphabetical_order(t_env *env)
{
	t_env	*list;
	t_env	*highest;

	list = env;
	highest = list;
	while (list)
	{
		if (ft_strncmp(list->var, highest->var, ft_strlen(highest->var)) > 0)
			highest = list;
		list = list->next;
	}
	return (highest);
}

static t_env	*find_next_in_alphabetical_order(t_env *env, t_env	*smallest)
{
	t_env	*list;
	t_env	*next;

	list = env;
	next = find_highest_in_alphabetical_order(env);
	while (list)
	{
		if (ft_strncmp(list->var, smallest->var, ft_strlen(smallest->var)) > 0
			&& ft_strncmp(list->var, next->var, ft_strlen(next->var)) < 0)
			next = list;
		list = list->next;
	}
	if (!ft_strncmp(next->var, smallest->var, ft_strlen(smallest->var)))
		return (NULL);
	return (next);
}

void	ft_export_child(t_env *env)
{
	t_env	*lst;
	t_env	*list_env;

	if (!env)
		return ;
	list_env = env;
	lst = find_smallest_in_alphabetical_order(env);
	while (list_env)
	{
		lst = find_next_in_alphabetical_order(env, lst);
		if (!lst)
			break ;
		printf("declare -x \"%s=%s\"\n", lst->var, lst->value);
		list_env = list_env->next;
	}
}
