/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:52:03 by bhumeau           #+#    #+#             */
/*   Updated: 2024/05/07 14:52:11 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# include <wait.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

# define ERR_QUOTE_NOT_CLOSED "syntax error: quotes aren't closed\n"
# define ERR_SPECIAL_CHAR "syntax error: special character\n"
# define ERR_PIPE_START "syntax error: starting by pipe\n"
# define ERR_PIPE_END "syntax error: ending by pipe\n"
# define ERR_EMPTY_PIPE "syntax error: empty pipe\n"
# define ERR_INVALID_REDIRECTION "syntax error: invalid redirection\n"
#endif
