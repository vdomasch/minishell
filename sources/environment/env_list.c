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

#include "../../includes/minishell.h"

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

char	*allocate_value(char *env)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;
	char			*value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (NULL);
	if (env[i + 1] == '\'' || env[i + 1] == '"')
		i++;
	len = ft_strlen(env) - i++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (env[i])
	{
		value[j] = env[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

char	*allocate_variable(char *env)
{
	unsigned int	i;
	unsigned int	j;
	char			*variable;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i - 1] == '\'' || env[i - 1] == '"')
		i--;
	variable = malloc(sizeof(char) * (i + 1));
	if (!variable)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (!(env[i + 1] == '=' && (env[i] == '\'' || env[i] == '"')))
		{
			variable[j] = env[i];
			j++;
		}
		i++;
	}
	variable[j] = '\0';
	return (variable);
}

bool	put_env_in_list(t_data *data, char **env)
{
	int		i;

	i = 0;
	data->env_list = env_lstnew(NULL);
	if (!data->env_list)
		return (false);
	if (env && *env)
	{
		data->env_list->var = allocate_variable(env[i]);
		data->env_list->value = allocate_value(env[i]);
		while (env[++i])
		{
			data->env_list->next = env_lstnew(data->env_list);
			if (!data->env_list->next)
				return (false);
			data->env_list = data->env_list->next;
			data->env_list->var = allocate_variable(env[i]);
			data->env_list->value = allocate_value(env[i]);
		}
	}
	data->env_list = env_first(data->env_list);
	return (true);
}
