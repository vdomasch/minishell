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
	if (pwd == NULL)
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
	if (save == NULL)
		return (NULL);
	tmp = ft_strrchr(save, '/') + 1;
	result = malloc(sizeof(char) * ft_strlen(tmp) + 3);
	if (result == NULL)
		return (NULL);
	while (tmp[i])
	{
		result[i] = tmp[i];
		i++;
	}
	result[i + 2] = tmp[i];
	result[i + 1] = ' ';
	result[i] = '$';
	free(save);
	return (result);
}

bool	str_is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_readline(t_data *data)
{
	char	*rl;
	char	*pwd;

	while (42)
	{
		pwd = ft_last_pwd();
		if (!pwd)
			rl = readline("$> ");
		else
			rl = readline(pwd);
		if (pwd)
			free(pwd);
		if (rl == NULL)
		{
			printf("exit\n");
			return ;
		}
		if (rl[0] != 0 && str_is_ascii(rl))
		{
			add_history(rl);
			if (process_message(data, rl) == 1)
				return (free(rl));
		}
		free(rl);
	}
}
