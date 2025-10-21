/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:46:56 by miricci           #+#    #+#             */
/*   Updated: 2025/10/21 12:29:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dst;
	int		len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = (char *) malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	*(dst + len) = 0;
	return (dst);
}
/*
int	main(void)
{
	char *str;
 	char *tmp = "I malloc so I am.";
 
 	str = ft_strdup(tmp);
 	printf("str: %s\n", str);
 	if (strcmp(str, tmp))
 	{
 		printf("TEST_FAILED");
 		return 0;
 	}
 	free(str);
 	printf("TEST_SUCCESS");
	return 0;
}
*/
