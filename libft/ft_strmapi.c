/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:53:16 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:53:18 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
/*
char	mapi(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c >= 'a' && c <= 'z') ? c - 32 : c;
	else
		return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = (f)(i, s[i]);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
/*
int	main(void)
{
	char const str[12];
	char *strmapi;
	strcpy((char *)str, "LoReM iPsUm");
	strmapi = ft_strmapi(str, &mapi);
	printf("%s", strmapi);
    	if (strmapi == str)
        	printf("\nA new string was not returned");
    	if (strmapi[11] != '\0')
        	printf("\nString is not null terminated");
}
*/
