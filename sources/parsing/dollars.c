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

bool	check_env_var_name(char *msg, t_env *list, int i)
{
	if (!ft_strncmp(msg + i, list->var, ft_strlen(list->var)))
	{
		i += ft_strlen(list->var);
		if ((!ft_isalnum(*(msg + i)) && *(msg + i) != '_') || *(msg + i) == 0)
			return (true);
	}
	return (false);
}

bool	replace_ret_value(char *msg, char *result, int *j, int *i)
{
	int		index;
	int		return_value;
	char	*chr_ret_value;

	if (msg[*i] == '?')
	{
		return_value = set_return_value(0);
		set_return_value(return_value);
		chr_ret_value = ft_itoa(return_value);
		if (!chr_ret_value)
		{
			set_return_value(2);
			return (false);
		}
		index = 0;
		while (chr_ret_value[index])
			result[(*j)++] = chr_ret_value[index++];
		result[(*j)] = '\0';
		free(chr_ret_value);
		(*i)++;
		return (true);
	}
	return (false);
}

static void	replace(t_data *data, char *result, int *i, int *j)
{
	int		k;
	bool	skip;
	t_env	*list;

	k = 0;
	(*i)++;
	skip = 0;
	list = env_first(data->env_list);
	while (list)
	{
		if (check_env_var_name(data->message, list, *i))
		{
			while (list->value[k])
				result[(*j)++] = list->value[k++];
			break ;
		}
		else if (replace_ret_value(data->message, result, j, i) && ++skip)
			break ;
		if (list->next)
			list = list->next;
		else
			break ;
	}
	while (!skip && (ft_isalnum(data->message[*i]) || data->message[*i] == '_'))
		(*i)++;
}

static char	*fill_and_replace(t_data *data, char *msg, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (msg[i])
	{
		if (is_expandable(msg, i))
			result[j++] = msg[i++];
		else
		{
			if (msg[i] == '\'' || msg[i] == '"')
				i++;
			else
			{
				if ((i > 0 && msg[i - 1] && msg[i + 1] && msg[i - 1] == '\"'
						&& msg[i] == '$' && msg[i + 1] == '\"'))
					result[j++] = msg[i++];
				else
					replace(data, result, &i, &j);
			}
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
	{
		perror("minishell: malloc: ");
		return (NULL);
	}
	result[len] = '\0';
	result = fill_and_replace(data, message, result);
	set_return_value(0);
	return (result);
}
