/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:35:15 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:35:20 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	i;

	i = 0;
	dst = (char *)malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (*s1)
	{
		dst[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		dst[i] = *s2;
		s2++;
		i++;
	}
	dst[i] = 0;
	return (dst);
}
/*
int	main(int ac, char **av)
{
	if(ac > 2)
		printf("%s\n", ft_strjoin(av[1], av[2]));
	return 0;
}
*/
