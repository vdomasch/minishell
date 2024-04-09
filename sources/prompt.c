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

void	ft_isterminal(void)
{
	int	fd;

	fd = 0;
	printf("isatty = %d\n", isatty(fd));
	printf("ttyname = %s\n", ttyname(fd));
}

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

int    ft_last_pwd(void)
{
    char    *save;
    char    *result;
    char    *tmp;
    int     i;

    i = 0;
    save = ft_getcwd();
    if (save == NULL)
        return (0);
    tmp = ft_strrchr(save, '/');
    result = malloc(sizeof(char) * ft_strlen(tmp) + 1);
    if (result == NULL)
        return (0);
    while (tmp[i])
    {
        result[i] = tmp[i];
        i++;
    }
    result[i] = tmp[i];
    printf("%s$", result);
    free(save);
    free(result);
    return (1);
}

void	ft_readline(void)
{
	char	*rl;

    if (ft_last_pwd() == 0)
        return ;
    rl = readline(" ");
    ft_process_message(rl);
	if (!ft_strncmp(rl, "exit", 5))
	{
		free(rl);
		return ;
	}
	/*else if (rl[0] == 'p' && rl[1] == 'w' && rl[2] == 'd' && rl[3] == '\0')
	{
		pwd = ft_getcwd();
		printf("%s\n", pwd);
		free(pwd);
	}*/
	else if (rl[0])
	{
		printf("minishell: command not found: %s\n", rl);
	}
	free(rl);
	ft_readline();
}
