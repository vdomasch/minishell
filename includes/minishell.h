/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:23:10 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/08 13:13:24 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_command
{
	char				**v_cmd;
	char 				*cmd;
	char				*redirect_output;
	char				*redirect_input;
	struct	s_command	*next;
	struct	s_command	*prev;
}	t_command;

typedef struct s_data
{
	t_command	*cmd_list;
	char		**v_path;
	size_t 		nb_pipes;
}	t_data;

char	*ft_getcwd(void);
void	ft_readline(t_data *data);
void	signal_set(void);
int 	process_message(t_data *data, const char *message);
char	**split_args(const char *s, char *set);

size_t	count_pipes(const char *str);
bool	is_in_quotes(const char *str, int j);
bool	is_invalid_char_in_quote(const char *str);
bool	are_quotes_closed(const char *str);
bool	is_empty_pipe(const char *str);
bool	is_ended_by_pipe(const char *str);
bool	is_starting_by_pipe(const char *str);

void	cmd_new(t_command	*prev);
void	free_cmd_list(t_command *cmd);
t_command	*cmd_last(t_command *lst);
void	print_all(t_command *cmd);

char	**split_arguments(const char *s, char *set);

#endif
