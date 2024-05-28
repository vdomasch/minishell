/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:26:18 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/10 13:26:20 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*find_element_env_list(t_env *list, char *str)
{
	while (list)
	{
		if (!ft_strncmp(list->var, "PWD", 4))
			break ;
		list = list->next;
	}
	return (list);
}

int	ch_env_pwd(t_data *data, char *path)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*var_path;
	char	*env_var_pwd;

	pwd = find_element_env_list(data->env_list, "PWD");
	oldpwd = find_element_env_list(data->env_list, "OLDPWD");
	var_path = ft_strjoin("OLDPWD=", pwd->value);
	if (!var_path)
		return (false);
	replace_existing_var(var_path, oldpwd, data);
	ft_free(var_path);
	if (chdir(path))
		return (false);
	var_path = ft_getcwd();
	env_var_pwd = ft_strjoin("PWD=", var_path);
	if (!var_path)
		return (false);
	replace_existing_var(env_var_pwd, pwd, data);
	ft_free(env_var_pwd);
	ft_free(var_path);
	return (true);
}

bool	relative_path(t_data *data, char *relative_path)
{
	char	*path;

	path = ft_getcwd();
	if (!path)
		return (false);
	path = ft_strfreejoin(ft_strfreejoin(path, "/"), relative_path);
	if (!path)
		return (false);
	if (!ch_env_pwd(data, path))
	{
		ft_free(path);
		return (false);
	}
	ft_free(path);
	return (true);
}

bool	ft_cd(t_data *data, char **v_cmd)
{
	t_env	*list;

	list = data->env_list;
	if (v_cmd[1] && v_cmd[2])
	{
		printf("cd: too many arguments\n");
		return (false);
	}
	else if (!v_cmd[1])
	{
		while (list && ft_strncmp(list->var, "HOME", 5))
			list = list->next;
		return (ch_env_pwd(data, list->value));
	}
	else if (v_cmd[1][0] == '/')
		return (ch_env_pwd(data, v_cmd[1]));
	else
		return (relative_path(data, v_cmd[1]));
}
