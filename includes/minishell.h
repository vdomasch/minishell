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
# include <wait.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_command
{
	char				**v_cmd;
	char				*cmd;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	t_command		*cmd_list;
	t_env			*env_list;
	char			*message;
	char			**v_path;
	unsigned int	nb_pipes;
}	t_data;

char		*ft_getcwd(void);
void		ft_readline(t_data *data);
void		signal_set(void);
int			process_message(t_data *data, char *message);

size_t		count_pipes(const char *str);
int			is_in_quotes(const char *str, int j);
bool		is_invalid_char_in_quote(const char *str);
bool		are_quotes_closed(const char *str);
bool		is_empty_pipe(const char *str);
bool		is_ended_by_pipe(const char *str);
bool		is_starting_by_pipe(const char *str);

bool		str_is_space(char *str);
bool		str_is_ascii(char *str);

char		*clean_command(char *cmd);

char		*replace_variables(t_data *data, char *message, t_env *env);

bool		create_cmd_list(t_data *data);
void		free_cmd_list(t_command *cmd);

t_command	*cmd_last(t_command *lst);

t_env		*env_lstnew(t_env *prev);
t_env		*env_first(t_env *env);
void		process_env(t_data *data, char **env);
void		free_env(t_env *env, char **v_path);
int			exec(t_data *data);

void		print_all(t_command *cmd);

char		**split_arguments(const char *s, char *set);

char		*ft_free_strtrim(char *s1, const char *s2);

#endif
