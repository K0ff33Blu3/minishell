/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:50:26 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:50:28 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	n = (n % 10) + 48;
	ft_putchar_fd(n, fd);
}
/*
int	main()
{
	int	file;
	
	file = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(file == -1)
	{
		printf("Errore apertura file");
		return 1;
	}
	printf("File aperto, file: %d\n", file);
	ft_putnbr_fd(-2147483648, file);
	close(file);
	return 0;

}
*/
