/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:01:18 by vdomasch          #+#    #+#             */
/*   Updated: 2024/05/09 14:01:20 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_redirection(t_command *cmd, int pipe_fd, int i)
{
	int		fd;
	char	*pathname;

	pathname = next_redirection_name(cmd, i);
	if (!pathname)
	{
		perror("minishell: malloc: ");
		return ;
	}
	fd = open(pathname, O_CREAT | O_APPEND | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pathname);
		exit(1);
	}
	if (!ft_strncmp(pathname, cmd->output_redirection, ft_strlen(pathname))
		&& check_last_redirection(cmd->cmd + i, '>'))
	{
		if (dup2(fd, pipe_fd) < 0)
			exit (1);
	}
	free(pathname);
	close(fd);
}

static void	trunc_redirection(t_command *cmd, int pipe_fd, int i)
{
	int		fd;
	char	*pathname;

	pathname = next_redirection_name(cmd, i);
	if (!pathname)
	{
		perror("minishell: malloc: ");
		return ;
	}
	fd = open(pathname, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pathname);
		exit(1);
	}
	if (!ft_strncmp(pathname, cmd->output_redirection, ft_strlen(pathname))
		&& check_last_redirection(cmd->cmd + i, '>'))
	{
		if (dup2(fd, pipe_fd) < 0)
			exit (1);
	}
	free(pathname);
	close(fd);
}

static void	input_redirection(t_command *cmd, int pipe_fd, int i)
{
	int		fd;
	char	*pathname;

	pathname = next_redirection_name(cmd, i);
	if (!pathname)
	{
		perror("minishell: malloc: ");
		return ;
	}
	fd = open(pathname, O_RDONLY, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pathname);
		exit(1);
	}
	if (!ft_strncmp(pathname, cmd->input_redirection, ft_strlen(pathname))
		&& check_last_redirection(cmd->cmd + i, '<'))
	{
		if (dup2(fd, pipe_fd) < 0)
			exit(1);
		close(fd);
	}
	free(pathname);
}

void	in_out_redirection(t_data *data, t_command *command, int pipe_fd, int i)
{
	if (command->cmd[i] == '>' || command->cmd[i] == '<')
		i++;
	if (command->cmd[i - 1] == '>' && command->cmd[i] == '>')
		append_redirection(command, pipe_fd, i + 1);
	else if (command->cmd[i - 1] == '>')
		trunc_redirection(command, pipe_fd, i);
	else if (command->cmd[i - 1] == '<' && command->cmd[i] == '<')
		heredoc_redirection(data, command, i + 1);
	else if (command->cmd[i - 1] == '<')
		input_redirection(command, pipe_fd, i);
}
