/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:18:57 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/07 17:19:00 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd)
	{
		printf("%s\n", pwd);
		ft_free(pwd);
		return (true);
	}
	return (false);
}
