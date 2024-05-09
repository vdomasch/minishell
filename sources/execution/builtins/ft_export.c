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



bool	new_var_in_list(char *cmd, t_env *env_list, char *var, char **env)
{
	t_env *new;

	new = env_lstnew(env_list);
	if (!new)
		return (false);
	new->var = var;
	new->value = allocate_value(cmd);
	if (!new->value)
	{
		free(new->var);
		new->prev->next = NULL;
		free(new);
		return (false);
	}
								(void)env;
	return (true);
}

bool	replace_existing_var_in_env(char *cmd, char *var, t_data *data)
{
	int		i;
	char	**new_env;
	char 	*tmp;

	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i + 1);
	if (!new_env)
		return (false);
	i = 0;
	while (new_env[i])
	{
		if (!ft_strncmp(var, cmd, ft_strlen(var)))
		{
			new_env[i] = ft_strdup(cmd);

		}
		else
			new_env[i] = data->env[i];
		i++;
	}
	tmp = data->env[i];
	free(data->env);
	free(tmp);
	data->env = new_env;
	return (true);
}

bool	replace_existing_var_in_list(char *cmd, t_env *env_list, t_data *data)
{
	if (env_list->value)
		free(env_list->value);
	env_list->value = allocate_value(cmd);
	if (!env_list->value)
		return (false);
	replace_existing_var_in_env(cmd, env_list->var, data);
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
			free(var);
			if (!replace_existing_var_in_list(cmd, tmp, data))
				return (false);
			return (true);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!new_var_in_list(cmd, tmp, var, data->env))
		return (false);
	return (true);
}

bool	ft_export(t_data *data)
{
	int i;
	t_env *tmp;

	i = 1;
	tmp = data->env_list;
	while (data->cmd_list->v_cmd[i])
	{
		if (!find_existing_var(data, data->cmd_list->v_cmd[i])) //verifier les frees
			return (false);
		i++;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		//printf("var = !%s! et value = !%s!\n", env_list->var, env_list->value);
	}
	return (true);
}