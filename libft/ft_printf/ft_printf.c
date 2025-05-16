/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:12:54 by miricci           #+#    #+#             */
/*   Updated: 2025/03/10 16:17:48 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_type(const int c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), c));
	if (c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;

	i = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			i += print_type(*format, args);
		}
		else
			i += ft_putchar(*format);
		format++;
	}
	return (i);
}
/*
int	main()
{
	int j = printf(" %x ", -10);
	printf("\n");
	int i = ft_printf(" %x ", -10);
	printf("\nreturn value ft_printf: %d\nreturn value printf: %d\n", i, j);
	return 0;
}
*/
