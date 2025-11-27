/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:36:23 by emondo            #+#    #+#             */
/*   Updated: 2025/11/27 18:27:02 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char *c)
{
	unsigned int	i;
	char			**metachar;
	int				len;

	i = 0;
	metachar = get_metachar();
	while (metachar[i])
	{
		len = ft_strlen(metachar[i]);
		if (!ft_strncmp(c, metachar[i], len))
			return (len);
		i++;
	}
	return (0);
}

int	skip_token(char *s, int i)
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

int	skip_quote(char *s, int start)
{
	char	quote;
	int		i;

	quote = s[start];
	i = start + 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

int	word_len(char *s, unsigned int start)
{
	int	len;

	len = 0;
	while (s[start] && !ft_isspace(s[start]) && !is_metachar(&s[start]))
	{
		if (s[start] == '\'' || s[start] == '\"')
			len = skip_quote(s, start);
		else
			len++;
		start++;
	}
	return (len);
}

int	quote_len(char *s, unsigned int start, char quote)
{
	int	len;

	len = 0;
	if (s[start] == quote)
	{
		len++;
		start++;
	}
	while (s[start] && s[start] != quote)
	{
		len++;
		start++;
	}
	if (s[start] == quote)
	{
		len++;
		start++;
	}
	return (len);
}
