/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:59:40 by miricci           #+#    #+#             */
/*   Updated: 2024/05/23 10:09:52 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	while (src[i])
		i++;
	if (size != 0)
	{
		while (size > 1 && *src)
		{
			*dst = *src;
			src++;
			dst++;
			size--;
		}
		*dst = '\0';
	}
	return (i);
}
/*
int	main (void)
{
	char dest[] = "Hello";
	char src[15];
	printf("%d", (int)ft_strlcpy(dest, src, 2));
	return (0);
}*/
