/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_ret_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:33:10 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/31 11:33:13 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_dollar_heredoc(char *msg, int i)
{
	while (i > 0 && (!ft_isspace(msg[i]) && msg[i] != '<'))
		i--;
	while (i > 0 && ft_isspace(msg[i]))
		i--;
	if (i > 0 && msg[i] == '<' && msg[i - 1] == '<')
		return (true);
	return (false);
}

bool	count_var_size(char *msg, t_env *list, int i, size_t *count)
{
	int		return_value;
	char	*chr_ret_value;

	if (check_env_var_name(msg, list, i))
	{
		*count += ft_strlen(list->value);
		return (true);
	}
	else if (msg[i] == '?')
	{
		return_value = set_return_value(0);
		set_return_value(return_value);
		chr_ret_value = ft_itoa(return_value);
		if (!chr_ret_value)
		{
			set_return_value(2);
			return (false);
		}
		*count += ft_strlen(chr_ret_value) - 1;
		free(chr_ret_value);
		return (true);
	}
	return (false);
}

size_t	count_size(char *msg, t_env *list, int i, size_t count)
{
	t_env *save;

	save = list;
	while (msg[i])
	{
		if (msg[i] != '$' || is_in_quotes(msg, i) == 1 || (msg[i + 1] != '?'
			&& !ft_isalnum(msg[i + 1]) && msg[i + 1] != '\'' && msg[i + 1] != '"' && msg[i + 1] != '_') || is_dollar_heredoc(msg, i))
			i++;
		else
		{
			i++;
			if (msg[i] == '\'' || msg[i] == '"')
			{
				if (msg[i - 1] != '$')
					count--;
				continue;
			}
			list = save;
			while (list)
			{
				if (count_var_size(msg, list, i, &count))
					break ;
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
