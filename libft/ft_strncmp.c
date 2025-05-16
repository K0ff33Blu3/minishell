/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:31:43 by miricci           #+#    #+#             */
/*   Updated: 2024/05/21 12:37:39 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((int)n == 0)
		return (0);
	if ((int)n < 0)
	{
		if (ft_strlen(s1) >= ft_strlen(s2))
			n = ft_strlen(s1);
		else
			n = ft_strlen(s2);
	}
	while ((int)n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == 0 || *s2 == 0)
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/*
int	main(void)
{
	char s1[] = "test\200";
	char s2[] = "test\0";
	int result = ft_strncmp(s1, s2, -1);
	int true_res = strncmp(s1, s2, -1);
	printf("result: %d\n", result);
	printf("true result: %d\n", true_res);
	return 0;
}
*/
