/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:01:49 by miricci           #+#    #+#             */
/*   Updated: 2024/12/08 18:34:58 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		i += ft_putchar('-');
		nbr *= -1;
	}
	if (nbr == -2147483648)
	{
		ft_putstr("2147483648");
		return (11);
	}
	if (nbr >= 10)
	{
		i += ft_putnbr(nbr / 10);
	}
	nbr = (nbr % 10) + 48;
	i += ft_putchar(nbr);
	return (i);
}
/*
int	main()
{
	ft_putnbr(-2147483648);
	return 0;
}
*/