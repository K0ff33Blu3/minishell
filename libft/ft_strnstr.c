/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:16:30 by miricci           #+#    #+#             */
/*   Updated: 2024/11/19 18:16:33 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <bsd/string.h>
#include "libft.h"
//	----- HA UN ARGOMENTO IN PIU DEL NORMALE STRCMP -------
static int	ft_strcmp(const char *str1, const char *str2,
	unsigned int i, size_t len)
{
	unsigned int	j;

	j = 0;
	while (str2[j] != 0 && i < (unsigned int)len)
	{
		if (str1[i] != str2[j])
			return (1);
		i++;
		j++;
		if (i == (unsigned int)len && j < ft_strlen(str2))
			return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (big[i] != 0 && i < (unsigned int)len)
	{
		if (ft_strcmp(big, little, i, len) == 0)
			return ((char *)big + i);
		i++;
	}
	return (0);
}
/*
int main()
{
	char *s1 = "oh no not the empty string !";
 	char *s2 = "";
 	size_t max = 0;
 	char *i1 = strnstr(s1, s2, max);
 	char *i2 = ft_strnstr(s1, s2, max);

 	printf("i1: %s\ni2: %s\n", i1, i2);
 	if (i1 == i2)
 	{
 		printf("TEST_SUCCESS");
 		return 0;
 	}
 	printf("TEST_FAILED");
 	return 0;
}
*/
