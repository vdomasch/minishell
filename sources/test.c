/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:35:41 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/03 11:35:42 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

void	ft_isterminal(void)
{
	int	fd;

	fd = 0;
	printf("isatty = %d\n", isatty(fd));	
	printf("ttyname = %s\n", ttyname(fd));

}

char	*ft_getcwd(void)
{
	char *pwd;
    
    pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("Error pwd!\n");
	}
	return (pwd);
}

void	ft_readline(void)
{
	char	*pwd;
    char	*rl;

	pwd = ft_getcwd();
	if (pwd == NULL)
		return ;
	printf("%s$ ", pwd);
	free(pwd);
    rl = readline("");
	if (rl[0] == 'e' && rl[1] == 'x' && rl[2] == 'i' && rl[3] == 't' && rl[4] == '\0')
	{
		free(rl);
		return ;
	}
	else if (rl[0] == 'p' && rl[1] == 'w' && rl[2] == 'd' && rl[3] == '\0')
	{
		pwd = ft_getcwd();
		printf("%s\n", pwd);
		free(pwd);
	}
	else if (!rl[0])
		printf("\n");
	else
	{
		printf("minishell: command not found: %s\n", rl);
	}
	free(rl);
	ft_readline();
}

int main(void)
{
	//struct sigaction	act;
	//sigset_t			mask;

	//sigemptyset(&mask);
	//act.sa_mask = mask;
	ft_readline();
	ft_isterminal();
    return (0);
}
