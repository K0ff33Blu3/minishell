/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:24:34 by miricci           #+#    #+#             */
/*   Updated: 2024/11/30 14:30:22 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void del_content(void *content)
{
    free(content);
}
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
int main(void)
{
	t_list	*tmp;
	t_list **lst;

    t_list *node1 = (t_list *)malloc(sizeof(t_list));
	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	t_list *node3 = (t_list *)malloc(sizeof(t_list));
    if (!node1 || !node2 || !node3)
        return (1);

    node1->content = strdup("Hello");
    node1->next = node2;
	node2->content = strdup("World");
	node2->next = node3;
	node3->content = strdup("!");
	node3->next = NULL;

	lst = &node1;
	tmp = *lst;

	while (tmp)
	{
    	printf("Before deletion: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	

    // Delete the node
    ft_lstdelone(node2, del_content);
	tmp = *lst;
	// SEGFAULT -- COMMENTARE PER CONTROLLARE L'ESISTENZA DI NODE3
	while (tmp)
	{
    	printf("After deletion: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("After deletion: %s\n", (char *)node3->content);

    return (0);
}
*/
