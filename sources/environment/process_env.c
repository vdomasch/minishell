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

#include "../../includes/minishell.h"

void	free_env(t_env *env, char **v_path)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (v_path)
	{
		while (v_path[i])
			i++;
		while (i-- > 0)
			ft_free(v_path[i]);
		ft_free(v_path);
	}
	if (env)
	{
		env = env_first(env);
		while (env)
		{
			tmp = env->next;
			ft_free(env->value);
			ft_free(env->var);
			ft_free(env);
			env = tmp;
		}
	}
}

char	**init_env(void)
{
	char	**env_array;

	env_array = malloc(sizeof(char *) * 4);
	if (!env_array)
		return (NULL);
	env_array[3] = NULL;
	env_array[0] = ft_strjoin("PWD=", ft_getcwd());
	env_array[1] = ft_strdup("SHLVL=1");
	env_array[2] = ft_strdup("_=/usr/bin/env");
	if (!env_array[0] || !env_array[1] || !env_array[2])
	{
		ft_free(env_array[2]);
		ft_free(env_array[1]);
		ft_free(env_array[0]);
		free(env_array);
		env_array = NULL;
	}
	return (env_array);
}

void	process_env(t_data *data, char **env)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (!env || !*env)
	{
		data->env = init_env();
		if (data->env && *data->env)
			put_env_in_list(data, data->env);
		return ;
	}
	put_env_in_list(data, env);
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
	data->env = copy_env(env);
	ft_free(path);
}
