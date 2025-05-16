/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:04:04 by miricci           #+#    #+#             */
/*   Updated: 2024/11/18 17:04:07 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	if (!dest && !src)
		return (NULL);
	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (src_c > dest_c)
	{
		while (n--)
			*dest_c++ = *src_c++;
	}
	else
	{
		dest_c += n;
		src_c += n;
		while (n--)
			*(--dest_c) = *(--src_c);
	}
	return (dest);
}
/*
int main() {
   char buffer[4] = "ciao";
   char dest[10];
   
   ft_memmove(dest, buffer, 10);
   printf("%s\n", dest);
   printf("indirizzo buffer: %p\nindirizzo dest: %p\n", buffer, dest);
   return 0;
}
*/
