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

static void	heredocument(t_command *cmd, char *eof, int fd)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_free(line);
	}
	clear_history();
	(void)cmd;
}

static void	heredoc_child(t_command *cmd, char *eof, int *fd)
{
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredocument(cmd, eof, fd[1]);
	close(fd[1]);
	exit(0);
}

static void	heredoc_parent(t_command *cmd, char *eof, int *fd)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	waitpid(0, &status, 0);
	signal_set();
	close(fd[1]);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			exit(EXIT_FAILURE);
		else
			if (!ft_strncmp(cmd->input_redirection, eof, ft_strlen(eof) + 1))
				dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	(void)eof;
	(void)cmd;
}

void	heredoc_redirection(t_command *cmd, int pipe_fd, int i)
{
	int		fd[2];
	int		pid;
	char	*pathname;

	pathname = next_redirection_name(cmd, i);
	if (!pathname)
		return ;
	(void)pipe_fd;
	if (pipe(fd) < 0)
	{
		printf("Pipe opening error\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
		heredoc_child(cmd, pathname, fd);
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		heredoc_parent(cmd, pathname, fd);
}
