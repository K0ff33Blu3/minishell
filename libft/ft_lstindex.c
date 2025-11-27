/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:34:53 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 12:43:57 by miricci          ###   ########.fr       */
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