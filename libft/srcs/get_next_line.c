/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:35:52 by vdomasch          #+#    #+#             */
/*   Updated: 2024/02/22 16:22:13 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	findnline(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (i + 1);
			i++;
		}
	}
	return (0);
}

static char	*read_line(int fd, char *buffer, char *stack)
{
	int		empty;
	int		value;

	empty = 0;
	value = 1;
	while (!findnline(stack) && value > 0)
	{
		value = read(fd, buffer, BUFFER_SIZE);
		if (value != -1)
			buffer[value] = '\0';
		if (value > 0)
		{
			stack = ft_strfreejoin(stack, buffer);
			empty = 1;
		}
	}
	if (stack && !empty && !stack[0])
	{
		free(stack);
		return (NULL);
	}
	return (stack);
}

static char	*extract_line(char	*stack)
{
	size_t	i;
	size_t	endl;
	char	*line;

	i = 0;
	if (!stack)
		return (NULL);
	endl = findnline(stack);
	if (!endl)
		return (ft_strdup(stack));
	line = malloc(sizeof(char) * (endl + 1));
	if (!line)
		return (NULL);
	line[endl] = '\0';
	while (i < endl)
	{
		line[i] = stack[i];
		i++;
	}
	return (line);
}

static void	extract_memory(char buffer[BUFFER_SIZE + 1])
{
	size_t	i;
	size_t	endl;

	i = 0;
	endl = findnline(buffer);
	if (endl)
	{
		while (buffer[endl])
			buffer[i++] = buffer[endl++];
		while (i <= BUFFER_SIZE)
			buffer[i++] = '\0';
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*stack;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (buffer[0] == '\n')
	{
		extract_memory(buffer);
		return (line_feed());
	}
	stack = ft_strdup(buffer);
	stack = read_line(fd, buffer, stack);
	if (!stack)
	{
		extract_memory(buffer);
		return (NULL);
	}
	line = extract_line(stack);
	extract_memory(buffer);
	if (stack)
		free(stack);
	return (line);
}

/*int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDWR);
	i = 10;
	while (i)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i--;
	}
	close(fd);
	return (0);
}*/
