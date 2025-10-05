/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/05 21:17:46 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_list **env_list, char **var)
{
	int	len;
	t_list	*node;
	int	i;
	

	i = 1;
	while (var[i])
	{
		printf("%s\n", var[i]);
		len = ft_strlen(var[i]);
		node = *env_list;
		while (node)
		{
			if (!ft_strncmp(var[i], node->next->content, len))
			{
				node->next =
				free(node);
				break ;
			}
			node = node->next;
		}
		i++;
	}
}