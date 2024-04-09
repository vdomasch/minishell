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

void	ft_isterminal(void);
char	*ft_getcwd(void);
void	ft_readline(void);
//int		ft_strncmp(const char *s1, const char *s2, size_t n);
//char	*ft_strtrim(char const *s1, char const *set);
//size_t	ft_strlen(const char *s);
void ft_process_message(char *message);
//char	**ft_split(const char *s, char c);

#endif
