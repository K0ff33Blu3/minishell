/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:24:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/12 15:09:37 by miricci          ###   ########.fr       */
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
			while (s[i] && !ft_isspace(s[i]) && !is_metachar(&s[i]))
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = skip_quote(s, i);
				else
					i++;
			}	
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
		if (is_metachar(&str[j]))
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

char	**re_tokenize(char **arr, int size)
{
	char	*joined;
	char	**token;

	joined = array_to_str(arr, " ", size);
	// ft_free((void **)arr, -1);
	if (!joined)
		return (NULL);
	token = tokenize(joined);
	free(joined);
	return (token);
}

// int	main()
// {
// 	// char	*array[4] = {
// 	// 	"ciao", "$$", "\"come\" ciao", "stai$"
// 	// };
// 	char *test = "ls -l";
// 	char	**res = tokenize(test);
// 	int	i = 0;
// 	while (res[i])
// 		printf("res: %s\n", res[i++]);
// 	ft_free((void **)res, -1);
// 	return (0);
// }