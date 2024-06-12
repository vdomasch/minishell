/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:55:13 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/17 10:55:16 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static void	heredocument(t_command *cmd, char *eof, int fd)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (!line)
			ft_putstr_fd("minishell: warning: here-document delimited by"
				"end-of-file\n", STDERR_FILENO);
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_free(line);
	}
	rl_clear_history();
	(void)cmd;
}

static void	heredoc_child(t_data *data, t_command *cmd, char *eof, int *fd)
{
	unsigned int	i;

	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredocument(cmd, eof, fd[1]);
	close(fd[1]);
	i = 3;
	while (i <= 1023)
		close(i++);
	free(eof);
	free_cmd_list(data->cmd_list);
	free_env(data->env_list, data->v_path);
	free_env(NULL, data->env);
	rl_clear_history();
	ft_free(data->message);
	ft_free(data->pipe_fds);
	exit(0);
}

static void	heredoc_parent(t_data *data, t_command *cmd, char *eof, int *fd)
{
	int	status;
	//int i;

	signal(SIGQUIT, SIG_IGN);
	waitpid(0, &status, 0);
	signal_set();
	close(fd[1]);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			exit(free_all(data, NULL, EXIT_FAILURE));
		else
			if (!ft_strncmp(cmd->input_redirection, eof, ft_strlen(eof) + 1))
				dup2(fd[0], STDIN_FILENO);
	}
	//i = 3;
	//while (i <= 1023)			NEEDED FOR ONE HEREDOC REDIRECTION
	//	close(i++);				ELSE MINISHELL EXIT
	(void)eof;
	(void)cmd;
}

void	heredoc_redirection(t_data *data, t_command *cmd, int i)
{
	int		fd[2];
	int		pid;
	char	*pathname;

	pathname = next_redirection_name(cmd, i);
	if (!pathname)
	{
		perror("minishell: malloc: ");
		return ;
	}
	if (pipe(fd) < 0)
	{
		printf("Pipe opening error\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
		heredoc_child(data, cmd, pathname, fd);
	else if (pid < 0)
		exit(free_all(data, pathname, EXIT_FAILURE));
	else
		heredoc_parent(data, cmd, pathname, fd);
	free(pathname);
}*/

void	heredoc_redirection(t_data *data, t_command *cmd, int i)
{
	char	*eof;

	eof = next_redirection_name(cmd, i);
	if (!eof)
		exit(free_all(data, eof, 2));
	if (!ft_strncmp(eof, cmd->input_redirection, ft_strlen(eof)))
	{
		cmd->heredoc_fd = open(".tmp.txt", O_RDONLY, 0666);
		if (cmd->heredoc_fd < 0)
			perror("minishell: heredocument");
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
			exit(free_all(data, eof, 1));
	}
	free(eof);
	close(cmd->heredoc_fd);
	i = 3;
	while (i <= 1023)
		close(i++);
}

static void	heredoc_rl(t_data *data, t_command *cmd, char *eof)
{
	char	*rl;

	(void)data;
	while (42)
	{
		rl = readline("> ");
		if (!rl)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by"
				"end-of-file (wanted '", STDERR_FILENO);
			ft_putstr_fd(eof, STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
		}
		if (!ft_strncmp(rl, eof, ft_strlen(eof)))
			break ;
		ft_putstr_fd(rl, cmd->heredoc_fd);
		ft_putstr_fd("\n", cmd->heredoc_fd);
		ft_free(rl);
	}
	ft_free(rl);
}

void	heredoc_init(t_data *data, t_command *cmd, int i)
{
	char	*eof;

	signal(SIGINT, &signal_heredoc);
	eof = next_redirection_name(cmd, i);
	if (!eof)
		exit(free_all(data, NULL, 2));
	save_free_data(data, eof, 1);
	cmd->heredoc_fd = open(".tmp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (cmd->heredoc_fd < 0)
	{
		perror("minishell: heredocument");
		exit(free_all(data, NULL, 1));
	}
	heredoc_rl(data, cmd, eof);
	close(cmd->heredoc_fd);
	exit(free_all(data, eof, 0));
}
