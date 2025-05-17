/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:54:44 by miricci           #+#    #+#             */
/*   Updated: 2025/05/16 13:00:48 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*current_path;
	int	bytes;
	
	current_path = getenv("PWD");
	bytes = printf("%s\n", current_path);
	if (bytes <= 0)
		exit (EXIT_FAILURE);
	return (bytes);
}
