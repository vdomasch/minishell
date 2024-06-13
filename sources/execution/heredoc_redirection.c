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
