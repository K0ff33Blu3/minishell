/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:24:24 by miricci           #+#    #+#             */
/*   Updated: 2025/05/27 17:39:52 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (s[i] == '\'' || s[i] == '\"')
				i = skip_quote(s, i);
			else
				while (s[i] && !ft_isspace(s[i]) && !is_metachar(&s[i]))
					i++;
		}
	}
	return (count);
}

char	*make_word(const char *s, int *j)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (word_len(s, *j) + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[*j] && !ft_isspace(s[*j]) && !is_metachar(&s[*j]))
		word[i++] = s[(*j)++];
	word[i] = 0;
	return (word);
}

char	*make_quote(const char *s, int *j)
{
	char	quote;
	char	*word;
	int		i;

	quote = s[*j];
	word = (char *)malloc(sizeof(char) * (quote_len(s, *j, quote) + 1));
	if (!word)
		return (NULL);
	word[0] = s[*j];
	(*j)++;
	i = 1;
	while (s[*j] && s[*j] != quote)
		word[i++] = s[(*j)++];
	if (s[*j] == quote)
		word[i++] = s[(*j)++];
	word[i] = 0;
	return (word);
}

char	*make_metachar(const char *s, int *j)
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

char	**tokenize(char	*str)
{
	int		i;
	int		j;
	char	**token;

	token = malloc(sizeof(char *) * (count_token(str) + 1));
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_token(str))
	{
		while (ft_isspace(str[j]))
			j++;
		if (str[j] == '\'' || str[j] == '\"')
			token[i] = make_quote(str, &j);
		else if (is_metachar(&str[j]))
			token[i] = make_metachar(str, &j);
		else
			token[i] = make_word(str, &j);
		if (!token[i])
			return (ft_free((void **)token, i), NULL);
		i++;
	}
	token[i] = NULL;
	return (token);
}

// int	main()
// {
// 	char	*test;
// 	int	n;
// 	char	**res;
// 	int	i;

// 	i = 0;
// 	test = "ciao come stai";
// 	res = tokenize(test);
// 	while (res[i])
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	ft_free((void **)res, -1);
// 	return 0;
// }