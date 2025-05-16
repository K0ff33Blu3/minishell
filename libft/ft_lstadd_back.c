/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:16:02 by miricci           #+#    #+#             */
/*   Updated: 2024/11/30 13:16:35 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}
/*
int	main(void)
{
	t_list *list = NULL;
	
	t_list *node1 = ft_lstnew("1");
	t_list *node2 = ft_lstnew("2");
	t_list *node3 = ft_lstnew("3");
	t_list *node4 = ft_lstnew("4");
	
	ft_lstadd_back(&list, node4);
	ft_lstadd_back(&list, node3);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node1);
	
	while(list)
	{
		printf("content: %s\nnext: %p\n", (char *)list->content, list->next);
		list = list->next;
	}
	return 0;
}
*/
