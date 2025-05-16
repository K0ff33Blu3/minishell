/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:32:14 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:32:16 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;
	int		j;
	size_t	max_len;

	i = 0;
	j = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	max_len = ft_strlen(s) - start;
	if (max_len > len)
		max_len = len;
	dst = (char *)malloc (sizeof(char) * (max_len + 1));
	if (!dst)
		return (NULL);
	while (s[i] && i < (char)start)
		i++;
	while (j < (int)max_len)
	{
		dst[j] = s[i + j];
		j++;
	}
	dst[j] = 0;
	return (dst);
}
/*
int	main()
{
	char *s = "tripouille";
 	//size_t size = strlen(s);
 	char *ret = ft_substr("tripouille", 0, 42000);
 	if (!strcmp(s, ret))
	{
 		printf("TEST_SUCCESS");
 		return 0;
 	}
 	free(ret);
 	printf("TEST_FAILED");
 	return(0);
}
*/
