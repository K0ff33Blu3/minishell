/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:36:48 by miricci           #+#    #+#             */
/*   Updated: 2025/03/10 16:17:32 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

int	ft_putptr(void *ptr);
int	ft_putchar(char c);
int	ft_putnbr(int nbr);
int	ft_putstr(const char *s);
int	ft_putnbr_hex(unsigned long nbr, char c);
int	ft_putnbr_unsigned(unsigned int nbr);
int	ft_printf(const char *format, ...);

#endif