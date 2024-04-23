/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_split_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:41 by bhumeau           #+#    #+#             */
/*   Updated: 2024/04/16 14:14:43 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static bool	char_sym(const char s, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i++] == s)
			return (1);
	}
	return (0);
}

unsigned int	move_to_current_word(const char *s, const char *set,
									 unsigned int current_word, unsigned int *start)
{
	unsigned int	i;
	unsigned int	simple_quotes;
	unsigned int	double_quotes;

	i = 0;
	simple_quotes = 0;
	double_quotes = 0;
	while (current_word--)
	{
		while (s[i] && char_sym(s[i], set))
			i++;
		if (s[i] && s[i] == '\'' && double_quotes % 2 == 0 && s[i++])
			simple_quotes++;
		if (s[i] && s[i] == '"' && simple_quotes % 2 == 0 && s[i++])
			double_quotes++;
		*start = i++;
		if (simple_quotes % 2 == 0 && double_quotes % 2 == 0)
			while (s[i] && !char_sym(s[i], set) && s[i] != '\'' && s[i] != '"')
				i++;
		else
			while (s[i] && s[i] != '\'' && s[i] != '"')
				i++;
	}
	return (i);
}

static unsigned int	count_word(const char *s, const char *charset,
								  unsigned int simple_quotes, unsigned int double_quotes)
{
	unsigned int	count;

	count = 0;
	while (*s)
	{
		if (*s == '\'' && double_quotes % 2 == 0 && s++)
			simple_quotes++;
		if (*s == '"' && simple_quotes % 2 == 0 && s++)
			double_quotes++;
		if (simple_quotes % 2 == 0 && double_quotes % 2 == 0)
		{
			while (*s && char_sym(*s, charset))
				s++;
			if (*s)
				count++;
			while (*s && !char_sym(*s, charset) && *s != '\'' && *s != '"')
				s++;
		}
		else
			while (*s != '\'' && *s != '"')
				s++;
	}
	return (count);
}

static char	*alloc(const char *s, const char *set, unsigned int current_word)
{
	char			*word;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	end = move_to_current_word(s, set, current_word, &start);
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**split_args(const char *s, char *set)
{
	char				**array;
	unsigned int		nb_word;
	unsigned int		current_word;

	current_word = 0;
	nb_word = count_word(s, set, 0, 0);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc(s, set, current_word);
		if (array[current_word - 1] == NULL)
		{
			while (current_word--)
				free(array[current_word]);
			free(array);
			return (NULL);
		}
	}
	array[current_word - 1] = NULL;
	return (array);
}
