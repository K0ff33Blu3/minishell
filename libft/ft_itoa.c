/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:39:54 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:39:57 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	magnitude(int nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
	}
	if (nbr == 0)
		return (0);
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static int	pow_ten(int n)
{
	int	result;

	result = 1;
	while (n > 0)
	{
		result *= 10;
		n--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		i;
	int		mgn;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	mgn = magnitude(n);
	nbr = (char *)malloc(sizeof(char) * (mgn + 2 + (n < 0)));
	if (!nbr)
		return (NULL);
	if (n < 0)
	{
		nbr[i++] = '-';
		n *= -1;
	}
	while (mgn >= 0)
	{
		nbr[i++] = (n / pow_ten(mgn)) + 48;
		n %= pow_ten(mgn--);
	}
	nbr[i] = 0;
	return (nbr);
}
/*
int	main(void)
{
	char *i1 = ft_itoa(-623);
	char *i2 = ft_itoa(156);
	char *i3 = ft_itoa(-0);

	if (strcmp(i1, "-623"))
	{
		printf("ft_itoa: %s\n", i1);
		printf("TEST_FAILED1");
		return 0;
	}
	if (strcmp(i2, "156"))
	{
		printf("ft_itoa: %s\n", i2);
		printf("TEST_FAILED2");
		return 0;
	}
	if (strcmp("0", i3))
	{
		printf("ft_itoa: %s\n", i3);
		printf("TEST_FAILED3");
		return 0;
	}
	printf("TEST_SUCCESS");
	return (0);
}
*/
