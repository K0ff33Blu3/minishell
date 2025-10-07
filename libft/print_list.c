/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:28:50 by miricci           #+#    #+#             */
/*   Updated: 2025/10/07 19:12:07 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_list(t_list **head, char *list_name)
{
	t_list	*node;
	char		*value;
	int		i;

	i = 1;
	node = *head;
	printf("\n------------%s---------------\n", list_name);
	while (node)
	{
		value = node->content;
		printf("node %d: \n", i);
		printf("content: %s\n", value);
		printf("next: %p\n", node->next);
		node = node->next;
		i++;
	}
	printf("------------%s---------------\n\n", list_name);
}
