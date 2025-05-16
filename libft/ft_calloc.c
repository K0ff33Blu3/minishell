/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:27:15 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:27:31 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, (nmemb * size));
	return (ptr);
}
/*
int	main(void)
{
	int	*array;
	int	i;
	
	i = 0;	
	array = (int *)ft_calloc(5, sizeof(int));
	
	if(!array)
		return (0);
	
	while(i < 5)
	{
		printf("%d, ", array[i]);
		i++;
	}
	return (0);
}
*/
