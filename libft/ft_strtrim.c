/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:39:08 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:39:10 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dst;
	int			start;
	int			end;
	int			len;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strrchr(set, s1[end - 1]))
		end--;
	len = end - start;
	dst = ft_substr(s1, start, len);
	if (!dst)
		return (NULL);
	return (dst);
}
/*
int	main(void)
{
	char	*str = "ABCABCKKhjkABC";
	char	*s = "ABC";
	
	printf("%s\n", ft_strtrim(str, s));
	return 0;
}
*/
