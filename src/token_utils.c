/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:36:23 by emondo            #+#    #+#             */
/*   Updated: 2025/10/09 16:39:37 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_metachar(void)
{
	static char	*metachar[18];

	metachar[0] = "||";
	metachar[1] = "&&";
	metachar[2] = "|";
	metachar[3] = "&";
	metachar[4] = "<<";
	metachar[5] = "<";
	metachar[6] = ">>";
	metachar[7] = ">";
	metachar[8] = "*";
	//metachar[9] = "?";
	metachar[10] = "[";
	metachar[11] = "]";
	metachar[12] = "(";
	metachar[13] = ")";
	metachar[14] = "{";
	metachar[15] = "}";
	metachar[16] = "\\";
	metachar[17] = NULL;
	return (metachar);
}

int	is_metachar(const char *c)
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

int	word_len(const char *s, unsigned int start)
{
	int	len;

	len = 0;
	while (s[start] && !ft_isspace(s[start]) && !is_metachar(&s[start]) 
			 && s[start] != '\'' && s[start] != '\"')
	{
		len++;
		start++;
	}
	return (len);
}

int	quote_len(const char *s, unsigned int start, char quote)
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
