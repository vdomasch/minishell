/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:16:50 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/12 15:16:52 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*allocate_value(char *env)
{
	int		i;
	int 	j;
	int 	len;
	char	*value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	len = ft_strlen(env) - i++;
	value = malloc(sizeof(char) * (len + 1));
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
	int		i;
	char	*variable;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (env[i] && env[i] != '=')
	{
		variable[i] = env[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

bool	put_env_in_list(t_data *data, char **env)
{
	int		i;

	i = 0;
	data->env_list = env_lstnew(NULL);
	if (!data->env_list)
		return (false);
	data->env_list->variable = allocate_variable(env[i]);
	data->env_list->value = allocate_value(env[i]);
	while (env[i])
	{
		data->env_list->next = env_lstnew(data->env_list);
		if (!data->env_list->next)
			return (false);
		data->env_list = data->env_list->next;
		data->env_list->variable = allocate_variable(env[i]);
		data->env_list->value = allocate_value(env[i]);
		i++;
	}
	return (true);
}

void	process_env(t_data *data, char **env)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (!env)
		return ;
	put_env_in_list(data, env);
	//print_env_list(data);
	while (env[i])
	{
		temp = ft_strnstr(env[i++], "PATH", 4);
		if (temp)
			break ;
	}
	if (!temp)
		return ;
	path = ft_strdup(temp + 5);
	data->v_path = ft_split(path, ':');
	free(path);
	return ;
}
