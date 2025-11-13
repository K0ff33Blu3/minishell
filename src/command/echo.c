/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:27:17 by miricci           #+#    #+#             */
/*   Updated: 2025/11/13 12:54:47 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char **cmd_args)
{
	int	i;
	int	j;

	i = 1;
	while (cmd_args[i])
	{
		if (!ft_strncmp(cmd_args[i], "-n", 2))
		{
			j = 1;
			while(cmd_args[i][j])
			{
				if (cmd_args[i][j] != 'n')
					return (i);
				j++;
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}

void	echo(t_cmd *data)
{
	int	i;
	int	flag;
	
	flag = check_flag(data->cmd_args);
	i = flag;
	while(data->cmd_args[i])
	{
		if (*(data->cmd_args[i]))
		{
			printf("%s", data->cmd_args[i]);
			if (data->cmd_args[i + 1])
				printf(" ");
		}
		i++;
	}
	if (flag == 1)
		printf("\n");
}
