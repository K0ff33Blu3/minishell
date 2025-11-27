/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:33:34 by elmondo           #+#    #+#             */
/*   Updated: 2025/11/27 17:33:35 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(str);
	return (token);
}
