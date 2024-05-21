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

bool	remove_in_env(t_data *data, char *cmd)
{
	//char	**new_env;

	printf("cmd = %s\n\n", cmd);
	(void)data;
	(void)cmd;
	return (true);
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
			if (!remove_in_env(data, cmd))
				return (true);
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