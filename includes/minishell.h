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

# include "error_messages.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <wait.h>

/* ************************************************************************** */
/*									STRUCT									  */
/* ************************************************************************** */

typedef struct s_heredoc
{
	char				*line;
	struct s_heredoc	*next;
}	t_heredoc;

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
	char				*input_redirection;
	char				*output_redirection;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	t_command		*cmd_list;
	t_env			*env_list;
	char			**env;
	char			*message;
	char			**v_path;
	int				return_value;
	unsigned int	nb_pipes;
}	t_data;

/* ************************************************************************** */
/*								MAIN FUNCTION								  */
/* ************************************************************************** */

void		process_env(t_data *data, char **env);
void		ft_readline(t_data *data);
int			process_message(t_data *data, char *message);

/* ************************************************************************** */
/*									SIGNALS									  */
/* ************************************************************************** */

void		signal_set(void);
void		signal_set_child(void);

/* ************************************************************************** */
/*									PARSING									  */
/* ************************************************************************** */

bool		are_quotes_closed(const char *str);
bool		create_cmd_list(t_data *data);
bool		is_empty_pipe(const char *str);
bool		is_ended_by_pipe(const char *str);
bool		is_invalid_char_in_quote(const char *str);
bool		is_redirection_valid(const char *str);
bool		is_starting_by_pipe(const char *str);
int			is_in_quotes(const char *str, int j);
char		*clean_command(char *cmd);
char		*replace_variables(t_data *data, char *message, t_env *env);
char		**split_arguments(const char *s, char *set);
void		free_cmd_list(t_command *cmd);
size_t		count_pipes(const char *str);

/* ************************************************************************** */
/*									EXECUTION								  */
/* ************************************************************************** */

bool		exec_builtins(t_data *data, t_command *cmd);
int			exec(t_data *data, t_command *cmd, int i);
void		exec_redirections(t_command *command, unsigned int nb_pipes,
				int *pipe_fds, unsigned int pipe_id);
void		heredoc_redirection(t_command *cmd, int pipe_fd, int i);
void		in_out_redirection(t_command *command, int pipe_fd, int i);
char		*next_redirection_name(t_command *cmd, int i);
void		pipes_commands(t_data *data, t_command *command, unsigned int i);

/* ************************************************************************** */
/*									ENVIRONMENT								  */
/* ************************************************************************** */

bool		put_env_in_list(t_data *data, char **env);
bool		replace_existing_var(char *cmd, t_env *env_list, t_data *data);
char		*allocate_variable(char *env);
char		*allocate_value(char *env);
char		**copy_env(char **env);
void		free_env(t_env *env, char **v_path);
t_env		*env_lstnew(t_env *prev);
t_env		*env_first(t_env *env);
t_env		*find_element_env_list(t_env *list, char *str);

/* ************************************************************************** */
/*									BUILTINS								  */
/* ************************************************************************** */

bool		ft_cd(t_data *data, char **v_cmd);
void		ft_echo(t_data *data, char **v_cmd);
void		ft_env(t_env *env_list);
void		ft_exit(t_data *data, t_command *cmd);
bool		ft_export(t_data *data, int i, int j);
void		ft_export_child(t_env *env);
bool		ft_pwd(void);
bool		ft_unset(t_data *data);

/* ************************************************************************** */
/*									UTILS								  */
/* ************************************************************************** */

int			set_return_value(unsigned char return_value);
void		ft_free(void *ptr);
char		*ft_free_strtrim(char *s1, const char *s2);
char		*ft_getcwd(void);
bool		is_there_chr(char *str, char c);
bool		str_is_space(char *str);
bool		str_is_ascii(char *str);
t_command	*cmd_last(t_command *lst);
t_command	*cmd_first(t_command *lst);

#endif
