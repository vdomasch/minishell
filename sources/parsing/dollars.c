/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:17:43 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/25 14:17:46 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_size(char *msg, t_env *env, int i, size_t count)
{
	while (msg[i])
	{
		if (msg[i] != '$' || is_in_quotes(msg, i) == 1
			|| !ft_isalnum(msg[i + 1]) || msg[i + 1] == '_')
			i++;
		else
		{
			i++;
			env = env_first(env);
			while (env->next)
			{
				if (!ft_strncmp(msg + i, env->var, ft_strlen(env->var)))
				{
					count += ft_strlen(env->value);
					break ;
				}
				env = env->next;
			}
			count += i - 1;
			while (ft_isalnum(msg[i]) || msg[i] == '_')
				i++;
			count -= i;
		}
	}
	return (count + i);
}

static void	replace(t_data *data, char *result, int *i, int *j)
{
	int	k;

	k = 0;
	(*i)++;
	data->env_list = env_first(data->env_list);
	while (data->env_list->next)
	{
		if (!ft_strncmp(data->message + *i, data->env_list->var,
				ft_strlen(data->env_list->var)))
		{
			while (data->env_list->value[k])
				result[(*j)++] = data->env_list->value[k++];
			break ;
		}
		data->env_list = data->env_list->next;
	}
	while (ft_isalnum(data->message[*i]) || data->message[*i] == '_')
		(*i)++;
}

static char	*fill_and_replace(t_data *data, char *message, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (message[i])
	{
		if (message[i] != '$' || is_in_quotes(message, i) == 1
			|| !ft_isalnum(message[i + 1]) || message[i + 1] == '_')
			result[j++] = message[i++];
		else
		{
			replace(data, result, &i, &j);
		}
	}
	return (result);
}

char	*replace_variables(t_data *data, char *message, t_env *env)
{
	char	*result;
	size_t	len;

	len = count_size(message, env, 0, 0);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	result = fill_and_replace(data, message, result);
	return (result);
}
