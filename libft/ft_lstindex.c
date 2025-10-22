/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:34:53 by miricci           #+#    #+#             */
/*   Updated: 2025/10/22 13:03:14 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstindex(t_list *head, t_list *target)
{
	int	index;
	t_list	*tmp;

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

// int	main()
// {
// 	t_list *list = NULL;
	
// 	t_list *node1 = ft_lstnew("primo");
// 	t_list *node2 = ft_lstnew("secondo");
// 	t_list *node3 = ft_lstnew("terzo");
// 	t_list *node4 = ft_lstnew("quarto");
	
// 	ft_lstadd_front(&list, node4);
// 	ft_lstadd_front(&list, node3);
// 	ft_lstadd_front(&list, node2);
// 	ft_lstadd_front(&list, node1);
	
// 	printf("list index: %d\n", ft_lstindex(list, node3));
// 	return 0;
// }