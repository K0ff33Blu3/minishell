/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:28:10 by miricci           #+#    #+#             */
/*   Updated: 2025/03/04 14:18:33 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	countwords(const char *s, char c)
{
	int	r;
	int	in_word;

	r = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			r++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (r);
}

static int	word_len(const char *s, unsigned int start, char end)
{
	int	i;

	i = 0;
	while (s[start] != end && s[start] != 0)
	{
		i++;
		start++;
	}
	return (i);
}

static char	**fill_split(char **dest, const char *s, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			j++;
		dest[i] = (char *)malloc(sizeof(char) * (word_len(s, j, c) + 1));
		if (!dest[i])
			return (ft_free((void **)dest, i), NULL);
		k = 0;
		while (s[j] && s[j] != c)
			dest[i][k++] = s[j++];
		dest[i][k] = '\0';
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		words;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	return (fill_split(dest, s, c, words));
}
