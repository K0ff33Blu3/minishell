/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:12:54 by miricci           #+#    #+#             */
/*   Updated: 2024/12/08 20:14:37 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				i;

	i = 0;
	address = (unsigned long)ptr;
	if (!address)
		return (ft_putstr("(nil)"));
	i += ft_putstr("0x");
	i += ft_putnbr_hex(address, 'x');
	return (i);
}
/*
int main()
{
    int i = ft_putptr((void *)LONG_MIN);
    printf("\n");
    int j = ft_putptr((void *)LONG_MAX);
    printf("\nLONG_MIN: %p\nLONG_MAX: %p", (void *)LONG_MIN, (void *)LONG_MAX);
    printf("\n%d\n%d\n", i, j);
    return (0);
}
*/