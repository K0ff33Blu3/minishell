/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:46:48 by miricci           #+#    #+#             */
/*   Updated: 2024/11/27 18:47:23 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd(10, fd);
}
/*
int	main(void)
{
	int	file;
	
	file = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		printf("Errore apertura file");
		return 1;
	}
	printf("File aperto, file: %d\n", file);
	ft_putendl_fd("mannaggia", file);
	close(file);
	return 0;
}
*/
