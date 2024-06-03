/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:35:41 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/08 12:59:17 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_colors(void)
{
	printf("Colors:\n"
	"\033[0;30mHello World! black\033[0m\n"
	"\033[0;31mHello World! red\033[0m\n"
	"\033[0;32mHello World! green\033[0m\n"
	"\033[0;33mHello World! yellow\033[0m\n"
	"\033[0;34mHello World! blue\033[0m\n"
	"\033[0;35mHello World! pink\033[0m\n"
	"\033[0;36mHello World! teal\033[0m\n"
	"\033[0;37mHello World! white\033[0m\n"
	"\nBold:\n"
	"\033[30;1mHello World! grey\033[0m\n"
	"\033[31;1mHello World! orange\033[0m\n"
	"\033[32;1mHello World! green\033[0m\n"
	"\033[33;1mHello World! yellow\033[0m\n"
	"\033[34;1mHello World! blue\033[0m\n"
	"\033[35;1mHello World! pink\033[0m\n"
	"\033[36;1mHello World! teal\033[0m\n"
	"\033[37;1mHello World! white\033[0m\n"
	"\nEffects:\n\n"
	"Black text effects:\n"
	"\033[30;2mHello World!\033[0m\n"
	"\033[30;3mHello World!\033[0m\n"
	"\033[30;4mHello World!\033[0m\n"
	"\033[30;5mHello World! blink\033[0m\n"
	"\033[30;6mHello World!\033[0m\n"
	"\033[30;7mHello World!\033[0m\n"
	"\033[30;8mHello World!\033[0m\n"
	"\nRed text effects:\n"
	"\033[31;2mHello World! faint\033[0m\n"
	"\033[31;3mHello World! normal\033[0m\n"
	"\033[31;4mHello World! underline\033[0m\n"
	"\033[31;5mHello World! blink\033[0m\n"
	"\033[31;6mHello World! normal, I think\033[0m\n"
	"\033[31;7mHello World! negative text\033[0m\n"
	"\nGreen text effects:\n"
	"\033[32;2mHello World! faint\033[0m\n"
	"\033[32;3mHello World! normal\033[0m\n"
	"\033[32;4mHello World! underline\033[0m\n"
	"\033[32;5mHello World! blink\033[0m\n"
	"\033[32;6mHello World! normal, I think\033[0m\n"
	"\033[32;7mHello World! negative text\033[0m\n"
	"\nYellow text effects:\n"
	"\033[33;2mHello World! faint\033[0m\n"
	"\033[33;3mHello World! normal\033[0m\n"
	"\033[33;4mHello World! underline\033[0m\n"
	"\033[33;5mHello World! blink\033[0m\n"
	"\033[33;6mHello World! normal, I think\033[0m\n"
	"\033[33;7mHello World! negative text\033[0m\n"
	"\nBlue text effects:\n"
	"\033[34;2mHello World! faint\033[0m\n"
	"\033[34;3mHello World! normal\033[0m\n"
	"\033[34;4mHello World! underline\033[0m\n"
	"\033[34;5mHello World! blink\033[0m\n"
	"\033[34;6mHello World! normal, I think\033[0m\n"
	"\033[34;7mHello World! negative text\033[0m\n"
	"\nPink text effects:\n"
	"\033[35;2mHello World! faint\033[0m\n"
	"\033[35;3mHello World! normal\033[0m\n"
	"\033[35;4mHello World! underline\033[0m\n"
	"\033[35;5mHello World! blink\033[0m\n"
	"\033[35;6mHello World! normal, I think\033[0m\n"
	"\033[35;7mHello World! negative text\033[0m\n"
	"\nTeal text effects:\n"
	"\033[36;2mHello World! faint\033[0m\n"
	"\033[36;3mHello World! normal\033[0m\n"
	"\033[36;4mHello World! underline\033[0m\n"
	"\033[36;5mHello World! blink\033[0m\n"
	"\033[36;6mHello World! normal, I think\033[0m\n"
	"\033[36;7mHello World! negative text\033[0m\n"
	"\nWhite text effects:\n"
	"\033[37;2mHello World! faint\033[0m\n"
	"\033[37;3mHello World! normal\033[0m\n"
	"\033[37;4mHello World! underline\033[0m\n"
	"\033[37;5mHello World! blink\033[0m\n"
	"\033[37;6mHello World! normal, I think\033[0m\n"
	"\033[37;7mHello World! negative text\033[0m\n"
	"\n");
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	t_command	command_list;

	//print_colors();
	(void)argc;
	(void)argv;
	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&data.cmd_list, 0, sizeof(t_command));
	data.cmd_list = &command_list;
	process_env(&data, env);
	if (!data.env)
	{
		perror("minishell: ");
		free_env(data.env_list, NULL);
		return (ENOMEM);
	}
	signal_set();
	ft_readline(&data);
	clear_history();
	free_env(data.env_list, data.v_path);
	if (data.env && *data.env && **data.env)
		free_env(NULL, data.env);
	return (0);
}
