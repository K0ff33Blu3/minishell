/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:37:34 by miricci           #+#    #+#             */
/*   Updated: 2025/03/04 14:46:45 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void del_content(void *content)
{
    free(content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
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

	lst = &node2;
	tmp = node1;
    
	while (tmp)
	{
    	printf("Before deletion: %s\n", (char *)tmp->content);
		tmp = tmp->next;

	}

    // Delete the node
    ft_lstclear(lst, del_content);
	if(lst == &node1)
    {
        if (!*lst)
            printf("LIST EMPTY");
        else
            printf("ERROR");
    }
    else
    {
        tmp = node1;
        while (tmp)
        {
            printf("SONO QUI");
            printf("content: %s\n", (char *)(tmp)->content);
            (tmp) = (tmp)->next;
        }
        
    }
    return (0);
}
*/
