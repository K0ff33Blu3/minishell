/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:34:53 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 16:34:05 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstindex(t_list *head, t_list *target)
{
	int	index;

	if (!head || !target)
		return (-1);
	index = 0;
	while (head)
	{
		if (head == target)
			return (index);
		index++;
		head = head->next;
	}
	return (-1);
}
