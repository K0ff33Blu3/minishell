/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:24:01 by miricci           #+#    #+#             */
/*   Updated: 2025/04/13 11:40:46 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sgn;

	nbr = 0;
	sgn = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sgn = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (!(*nptr >= 48 && *nptr <= 57))
			return (sgn * nbr);
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
	}
	return (sgn * nbr);
}
/*
int	main(void)
{	
	char *n = "\010 8";
 	int i1 = atoi(n);
 	int i2 = ft_atoi(n);
 	printf("atoi: %d\nft_atoi: %d\n", i1, i2);
 
 	if (i1 == i2)
 	{
 		printf("TEST_SUCCESS");
 		return 0;
 	}
 	printf("TEST_FAILED");
 	return 0;
}
*/
