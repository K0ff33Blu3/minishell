/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:24:24 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:28:13 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_token(char *s, int i)
{
	while (s[i] && !ft_isspace(s[i]) && !is_metachar(&s[i]))
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = skip_quote(s, i);
		else
			i++;
	}
	return (i);
}

int	count_token(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		else if (is_metachar(&s[i]))
		{
			count++;
			i += is_metachar(&s[i]);
		}
		else
		{
			count++;
			i = skip_token(s, i);
		}
	}
	return (count);
}

char	*make_word(char *s, int *j)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (word_len(s, *j) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[*j] && !ft_isspace(s[*j]) && !is_metachar(&s[*j]))
	{
		if (s[*j] == '\'' || s[*j] == '\"')
			make_quote(&word, s, j, &i);
		else
			word[i++] = s[(*j)++];
	}
	word[i] = 0;
	return (word);
}

void	make_quote(char **word, char *s, int *j, int *i)
{
	char	quote;

	quote = s[*j];
	(*word)[*i] = quote;
	(*j)++;
	(*i)++;
	while (s[*j] && s[*j] != quote)
		(*word)[(*i)++] = s[(*j)++];
	if (s[*j] == quote)
		(*word)[(*i)++] = s[(*j)++];
}

char	*make_metachar(char *s, int *j)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = is_metachar(&s[*j]);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
		word[i++] = s[(*j)++];
	word[len] = 0;
	return (word);
}
