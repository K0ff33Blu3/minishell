/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:29:29 by miricci           #+#    #+#             */
/*   Updated: 2024/12/02 13:29:32 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void to_uppercase(void *content)
{
    char *str = (char *)content;
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
            *str -= 32;
        str++;
    }
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
int main(void)
{
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));
    t_list *tmp;

    if (!node1 || !node2 || !node3)
        return (1);

    // Inizializza i nodi
    node1->content = "hello";
    node1->next = node2;

    node2->content = "world";
    node2->next = node3;

    node3->content = "list";
    node3->next = NULL;

    // Stampa la lista prima dell'iterazione
    printf("Before ft_lstiter:\n");
    tmp = node1;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    // Applica ft_lstiter con la funzione to_uppercase
    ft_lstiter(node1, to_uppercase);

    // Stampa la lista dopo l'iterazione
    printf("\nAfter ft_lstiter:\n");
    tmp = node1;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
    return (0);
}
*/
