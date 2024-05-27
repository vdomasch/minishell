/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:32:40 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/17 15:32:45 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	remove_in_env(t_data *data, char *cmd, int i)
{
	char	**new_env;
	char	**tmp;
	int		j;

	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (false);
	i = 0;
	j = 0;
	while (data->env[i + j])
	{
		if (j == 0 && !ft_strncmp(data->env[i], cmd, ft_strlen(cmd)) && ++j)
			ft_free(data->env[i]);
		new_env[i] = data->env[i + j];
		if (data->env[i + j])
			i++;
	}
	new_env[i] = NULL;
	tmp = data->env;
	data->env = new_env;
	ft_free(tmp);
	return (true);
}

void	remove_in_env_list(t_data *data, char *cmd)
{
	t_env	*tmp;

	tmp = data->env_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, cmd, ft_strlen(cmd)))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_free(tmp->var);
			ft_free(tmp->value);
			ft_free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

bool	find_existing_var_unset(t_data *data, char *cmd)
{
	t_env	*tmp;

	tmp = data->env_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, cmd, ft_strlen(cmd)))
		{
			remove_in_env_list(data, cmd);
			if (!remove_in_env(data, cmd, 0))
				return (false);
			return (true);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	ft_unset(t_data *data)
{
	int		i;

	i = 1;
	while (data->cmd_list->v_cmd[i])
	{
		if (!find_existing_var_unset(data, data->cmd_list->v_cmd[i]))
			return (false);
		i++;
	}
	return (true);
}
