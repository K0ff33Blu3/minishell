/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:59:07 by miricci           #+#    #+#             */
/*   Updated: 2025/03/04 15:16:46 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc (sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int main()
{
	t_list	*elem;
	char    str [] = "lorem ipsum dolor sit";
    	if (!(elem = ft_lstnew(str)))
            printf("NULL");
    	else
    	{
        	if (!(elem->content))
        		printf("NULL");
        	else
            		printf("%s\n", (char *)elem->content);
        	if (!(elem->next))
        	{
           		write(1, "\n", 1);
            		printf("NULL");
        	}
        }
	return 0;
}

int	main(void)
{
	char *content = "Milva";
	t_list *nodo = ft_lstnew((void *)content);
	
	if(nodo)
	{
		printf("Content: %s\nNext: %p\n", (char *)nodo->content, nodo->next);
		free(nodo);
	}
	else
		printf("ERROR");
	return (0);
}
*/
