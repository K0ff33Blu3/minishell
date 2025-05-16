/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:23:56 by miricci           #+#    #+#             */
/*   Updated: 2024/12/08 20:05:11 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr >= 10)
		i += ft_putnbr_unsigned(nbr / 10);
	nbr = (nbr % 10) + 48;
	i += ft_putchar(nbr);
	return (i);
}
/*
int	main()
{
	unsigned int i = ft_putnbr_unsigned(0);
	ft_putchar('\n');
	ft_putnbr(i);
	return 0;
}
*/