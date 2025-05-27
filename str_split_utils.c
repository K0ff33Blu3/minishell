/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:52 by miricci           #+#    #+#             */
/*   Updated: 2025/03/22 15:54:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_len(const char *s, unsigned int start, char end)
{
	int	i;

	i = 0;
	while (s[start] && s[start] != end)
	{
		i++;
		start++;
	}
	return (i);
}

static char	*make_word(const char *s, char c, int *j)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (word_len(s, *j, c) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[*j] && s[*j] != c)
		word[i++] = s[(*j)++];
	word[i] = 0;
	return (word);
}

static char	*make_quote(const char *s, int *j)
{
	char	quote;
	char	*word;

	quote = s[*j];
	(*j)++;
	word = make_word(s, quote, j);
	if (!word)
		return (NULL);
	if (s[*j] == quote)
		(*j)++;
	return (word);
}

char	**fill_split(char **dest, const char *s, char c, int words)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			j++;
		if (s[j] == 39 || s[j] == 34)
		{
			dest[i] = make_quote(s, &j);
			if (!dest[i])
				return (ft_free((void **)dest, i), NULL);
		}
		else
		{
			dest[i] = make_word(s, c, &j);
			if (!dest[i])
				return (ft_free((void **)dest, i), NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
