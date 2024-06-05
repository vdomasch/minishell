/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:53:31 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/08 13:12:34 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error pwd!\n");
		return (NULL);
	}
	return (pwd);
}

char	*ft_last_pwd(void)
{
	char	*save;
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	save = ft_getcwd();
	if (!save)
		return (NULL);
	tmp = ft_strrchr(save, '/') + 1;
	result = malloc(sizeof(char) * ft_strlen(tmp) + 3);
	if (result)
	{
		while (tmp[i])
		{
			result[i] = tmp[i];
			i++;
		}
		result[i + 2] = tmp[i];
		result[i + 1] = ' ';
		result[i] = '$';
	}
	ft_free(save);
	return (result);
}

void	ft_readline(t_data *data)
{
	char	*rl;
	char	*pwd;

	while (42)
	{
		signal_set();
		pwd = ft_last_pwd();
		if (!pwd)
			rl = readline("\001\033[31;5m\002$> \001\033[0m\002");
		else
			rl = readline(pwd);
		ft_free(pwd);
		if (!rl)
		{
			printf("exit\n");
			return ;
		}
		if (rl[0] != 0 && str_is_ascii(rl))
		{
			add_history(rl);
			if (!str_is_space(rl) && process_message(data, rl) == 1)
				return (ft_free(rl));
		}
		ft_free(rl);
	}
}
