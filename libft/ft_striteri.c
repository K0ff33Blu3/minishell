/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:44:20 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:44:27 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/*
void	ft_bzero(unsigned int i, char *s)
{
	while (s[i])
	{
		s[i] = '0';
		i++;
	}
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(f)(i, s + i);
		i++;
	}
}
/*
int	main(int ac, char ** av)
{
	if(ac > 1)
	{
		ft_striteri(av[1], ft_bzero);
		printf("%s\n", av[1]);
	}
	return 0;
}
*/
