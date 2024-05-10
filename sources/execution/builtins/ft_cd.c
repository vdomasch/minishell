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

bool	relative_path(char *relative_path)
{
	char	*path;

	path = ft_getcwd();
	if (!path)
		return (false);
	path = ft_strfreejoin(ft_strfreejoin(path, "/"), relative_path);
	if (!path)
		return (false);
	if (!chdir(path))
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	ft_cd(t_data *data, char **v_cmd)
{
	if (v_cmd[1] && v_cmd[2])
	{
		printf("cd: too many arguments\n");
		return (false);
	}
	else if (!v_cmd[1])
		return (chdir("/home/bhumeau"));
	else if (v_cmd[1][0] == '/')
		return (chdir(v_cmd[1]));
	else
		return (relative_path(v_cmd[1]));
	(void)data;
	//change_env();
}