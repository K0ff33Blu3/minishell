/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:59:47 by miricci           #+#    #+#             */
/*   Updated: 2025/05/16 12:52:03 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *str, int n)
{
	int	bytes;

	if (n == 0)
		bytes = printf("%s\n", str);
	else
		bytes = printf("%s%%\n", str);
	return (bytes);	
}