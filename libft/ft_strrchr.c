/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:52:28 by miricci           #+#    #+#             */
/*   Updated: 2024/11/19 11:52:33 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		else
			i--;
	}
	if (!c)
		return ((char *)s);
	return (NULL);
}
/*
int	main(void)
{
	char	*str = "Milvla";
	char	c = 'l';
	
	printf("%s\n", ft_strrchr(str, c));
	return 0;
}
*/
