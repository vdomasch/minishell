/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:34:24 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/08 13:34:26 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**new_var_in_env(char *cmd, t_data *data)
{
	unsigned int	i;
	char			**new_env;

	i = 0;
	while (data->env[i++])
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (data->env);
	new_env[i] = NULL;
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(cmd);
	if (!new_env[i])
	{
		ft_free(new_env);
		return (data->env);
	}
	ft_free(data->env);
	return (new_env);
}

bool	new_var_in_list(char *cmd, t_env *env_list, char *var, t_data *data)
{
	t_env	*new;

	new = env_lstnew(env_list);
	if (!new)
		return (false);
	new->var = var;
	new->value = allocate_value(cmd);
	if (!new->value && is_there_chr(cmd, '=') && *ft_strrchr(cmd, '=') + 1 != '\0')
	{
		ft_free(new->var);
		new->prev->next = NULL;
		ft_free(new);
		return (false);
	}
	data->env = new_var_in_env(cmd, data);
	if (!data->env)
	{
		ft_free(new->var);
		ft_free(new->value);
		new->prev->next = NULL;
		ft_free(new);
		return (false);
	}
	return (true);
}

bool	replace_existing_var(char *cmd, t_env *env_list, t_data *data)
{
	int		i;
	t_env	*list;
	char	*tmp;

	if (env_list->value)
		ft_free(env_list->value);
	env_list->value = allocate_value(cmd);
	if (!env_list->value)
		return (false);
	list = data->env_list;
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(list->var, cmd, ft_strlen(list->var)))
		{
			tmp = ft_strdup(cmd);
			if (!tmp)
				return (false);
			ft_free(data->env[i]);
			data->env[i] = tmp;
		}
		list = list->next;
		i++;
	}
	return (true);
}

bool	find_existing_var(t_data *data, char *cmd)
{
	char	*var;
	t_env	*tmp;

	var = allocate_variable(cmd);
	if (!var)
		return (false);
	tmp = data->env_list;
	while (42)
	{
		if (!strncmp(tmp->var, var, ft_strlen(var))
			&& !strncmp(tmp->var, var, ft_strlen(tmp->var)))
		{
			ft_free(var);
			if (!replace_existing_var(cmd, tmp, data))
				return (false);
			return (true);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!new_var_in_list(cmd, tmp, var, data))
		return (false);
	return (true);
}

bool	ft_export(t_data *data)
{
	int		i;

	i = 1;
	while (data->cmd_list->v_cmd[i])
	{
		if (!find_existing_var(data, data->cmd_list->v_cmd[i]))
			return (false);
		i++;
	}
	return (true);
}
