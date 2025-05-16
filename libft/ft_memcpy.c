/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:20 by miricci           #+#    #+#             */
/*   Updated: 2024/11/18 16:53:00 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	if (!dest && !src)
		return (NULL);
	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (n == 0)
		return (dest);
	while (n > 0)
	{
		*dest_c = *src_c;
		dest_c++;
		src_c++;
		n--;
	}
	return (dest);
}
/*
int main() {
   char *buffer = "ciao";
   char dest[10];
   //int	i;
   
   //i = 0;  
   //dest = (char *)malloc (sizeof(char) * strlen(buffer));
   ft_memcpy(dest, buffer, 5);
   printf("%s\n", dest);
   printf("indirizzo buffer: %p\nindirizzo dest: %p\n", buffer, dest);
   while (i < 10)
   {
      printf("%c ", dest[i]);
      i++;
   }
   return 0;
}
*/
