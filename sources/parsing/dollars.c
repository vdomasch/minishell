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

static bool	check_env_var_name(char *msg, t_env *list, int i)
{
	if (!ft_strncmp(msg + i, list->var, ft_strlen(list->var)))
	{
		i += ft_strlen(list->var);
		if ((!ft_isalnum(*(msg + i)) && *(msg + i) != '_') || *(msg + i) == 0)
			return (true);
	}
	return (false);
}

static size_t	count_size(char *msg, t_env *list, int i, size_t count)
{
	while (msg[i])
	{
		if (msg[i] != '$' || is_in_quotes(msg, i) == 1
			|| !ft_isalnum(msg[i + 1]) || msg[i + 1] == '_')
			i++;
		else
		{
			i++;
			list = env_first(list);
			while (list)
			{
				if (check_env_var_name(msg, list, i))
				{
					count += ft_strlen(list->value);
					break ;
				}
				list = list->next;
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
	int		k;
	t_env	*list;

	k = 0;
	(*i)++;
	list = env_first(data->env_list);
	while (list)
	{
		if (check_env_var_name(data->message, list, *i))
		{
			while (list->value[k])
				result[(*j)++] = list->value[k++];
			break ;
		}
		if (list->next)
			list = list->next;
		else
			break ;
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
