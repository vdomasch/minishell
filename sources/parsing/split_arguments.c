/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:12:58 by vdomasch          #+#    #+#             */
/*   Updated: 2024/04/10 12:13:00 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static unsigned int	move_to_current_word(const char *s, const char *set,
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
		while (s[i] && (char_sym(s[i], set) || ft_isspace(s[i])))
			i++;
		//if (s[start] == '\'' || s[start] == '"')
		//	start++;
		*start = i;
		while (s[i] && (is_in_quotes(s, (int)i) || !ft_isspace(s[i])
						|| !char_sym(s[i], set)))
			i++;
	}
	return (i);
}

unsigned int	count_quotes(const char *s, unsigned int start, unsigned int end)
{
	unsigned int	count;
	int				quotes;

	count = 0;
	quotes = 0;
	while (start <= end)
	{
		if ((s[start] == '\'' || s[start] == '"') && quotes == 0)
		{
			if (s[start] == '\'')
				quotes--;
			else
				quotes++;
			count++;
		}
		else if (((s[start] == '\'' && quotes == -1 )|| (s[start] == '"' && quotes == 1)))
		{
			quotes = 0;
			count++;
		}
		start++;
	}
	return (count);
}

void copy_without_quotes(char *word, const char *s, unsigned int start, unsigned int end)
{
	int 			quotes;
	unsigned int	i;

	i = 0;
	quotes = 0;
	while (start <= end)
	{
		if ((s[start] == '\'' || s[start] == '"') && quotes == 0)
		{
			if (s[start] == '\'')
				quotes--;
			else
				quotes++;
		}
		else if (((s[start] == '\'' && quotes == -1) || (s[start] == '"' && quotes == 1)))
			quotes = 0;
		else
			word[i++] = s[start];
		start++;
	}
	word[i - 1] = '\0';
}

static char	*alloc(const char *s, const char *set, unsigned int current_word)
{
	char			*word;
	unsigned int	start;
	unsigned int	end;

	end = move_to_current_word(s, set, current_word, &start);
	word = (char *)malloc(sizeof(char) * (end - start + 1 - count_quotes(s, start, end)));
	if (!word)
		return (NULL);
	copy_without_quotes(word, s, start, end);
	return (word);
}

static unsigned int	count_word(const char *s, const char *charset)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (char_sym(s[i], charset) || ft_isspace(s[i])))
			i++;
		if (s[i] == '\'' || s[i] == '"')
			i++;
		if (s[i])
			count++;
		while (s[i] && (is_in_quotes(s, (int)i) || !ft_isspace(s[i])
						|| !char_sym(s[i], charset)))
			i++;
	}
	return (count);
}

char	**split_arguments(const char *s, char *set)
{
	char				**array;
	unsigned int		nb_word;
	unsigned int		current_word;

	current_word = 0;
	nb_word = count_word(s, set);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc(s, set, current_word);
		if (array[current_word - 1] == NULL)
		{
			while (current_word--)
				ft_free(array[current_word]);
			ft_free(array);
			return (NULL);
		}
	}
	array[current_word - 1] = NULL;
	return (array);
}

/*
static bool	char_sym(const char s, const char *charset)
{
	int	start;

	start = 0;
	while (charset[start])
	{
		if (charset[start++] == s)
			return (1);
	}
	return (0);
}

static unsigned int	move_to_current_word(const char *s, const char *set,
					unsigned int current_word, unsigned int *start)
{
	unsigned int	start;
	unsigned int	simple_quotes;
	unsigned int	double_quotes;

	start = 0;
	simple_quotes = 0;
	double_quotes = 0;
	while (current_word--)
	{
		while (s[start] && (char_sym(s[start], set) || ft_isspace(s[start])))
			start++;
		if (s[start] == '\'' || s[start] == '"')
			start++;
		*start = start;
		while (s[start] && (is_in_quotes(s, (int)start) || !ft_isspace(s[start])
				|| !char_sym(s[start], set)))
			start++;
	}
	if (s[start - 1] == '\'' || s[start - 1] == '"')
		start--;
	return (start);
}

static char	*alloc(const char *s, const char *set, unsigned int current_word)
{
	char			*word;
	unsigned int	start;
	unsigned int	start;
	unsigned int	end;

	end = move_to_current_word(s, set, current_word, &start);
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	start = 0;
	while (start < end)
		word[start++] = s[start++];
	word[start] = '\0';
	return (word);
}

static unsigned int	count_word(const char *s, const char *charset)
{
	unsigned int	count;
	unsigned int	start;

	start = 0;
	count = 0;
	while (s[start])
	{
		while (s[start] && (char_sym(s[start], charset) || ft_isspace(s[start])))
			start++;
		if (s[start] == '\'' || s[start] == '"')
			start++;
		if (s[start])
			count++;
		while (s[start] && (is_in_quotes(s, (int)start) || !ft_isspace(s[start])
				|| !char_sym(s[start], charset)))
			start++;
	}
	return (count);
}

char	**split_arguments(const char *s, char *set)
{
	char				**array;
	unsigned int		nb_word;
	unsigned int		current_word;

	current_word = 0;
	nb_word = count_word(s, set);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc(s, set, current_word);
		if (array[current_word - 1] == NULL)
		{
			while (current_word--)
				ft_free(array[current_word]);
			ft_free(array);
			return (NULL);
		}
	}
	array[current_word - 1] = NULL;
	return (array);
}
*/