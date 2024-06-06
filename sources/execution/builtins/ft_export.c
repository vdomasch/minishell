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

char	**new_var_in_env(char *cmd, t_data *data, bool *success)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->env[i++])
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		*success = false;
		return (data->env);
	}
	new_env[i] = NULL;
	i = -1;
	while (data->env[++i])
		new_env[i] = data->env[i];
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
	bool	success;

	success = true;
	new = env_lstnew(env_list);
	if (!new)
		return (false);
	new->var = var;
	new->value = allocate_value(cmd);
	data->env = new_var_in_env(cmd, data, &success);
	if ((!new->value && is_there_chr(cmd, '=')
			&& *ft_strrchr(cmd, '=') + 1 != '\0') || (!success))
	{
		ft_free(new->var);
		ft_free(new->value);
		new->prev->next = NULL;
		ft_free(new);
		perror("minishell: malloc: ");
		return (false);
	}
	return (true);
}

bool	replace_existing_var(char *cmd, t_env *env_list, t_data *data)
{
	int		i;
	t_env	*list;
	char	*tmp;

	tmp = env_list->value;
	env_list->value = allocate_value(cmd);
	ft_free(tmp);
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

bool	ft_export(t_data *data, char **v_cmd, int i, int j)
{
	while (v_cmd[i])
	{
		j = 0;
		while (j >= 0 && v_cmd[i][j]
			&& v_cmd[i][j] != '=')
		{
			if (!ft_isalnum(v_cmd[i][j])
				&& v_cmd[i][j] != '_' && v_cmd[i][j] != '=')
				j = -2;
			j++;
		}
		if (j == -1 || ft_isdigit(v_cmd[i][0]) || v_cmd[i][0] == '=')
		{
			ft_putstr_fd("minishell: export: \'", 2);
			ft_putstr_fd(v_cmd[i++], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			set_return_value(1);
			continue ;
		}
		if (!find_existing_var(data, v_cmd[i]))
			return (false);
		i++;
	}
	return (true);
}
