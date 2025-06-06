/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:46:26 by miricci           #+#    #+#             */
/*   Updated: 2025/06/03 11:51:54 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	// if (!s)
	// 	write(fd, "(null)", 6);
	while (*s)
		write(fd, s++, 1);
}
/*
int	main(void)
{
	int	file;
	
	file = open("file1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(file == -1)
	{
		printf("Errore apertura file");
		return 1;
	}
	printf("File aperto, file: %d\n", file);
	ft_putstr_fd("CIAO", file);
	close(file);
	return 0;
}
*/
