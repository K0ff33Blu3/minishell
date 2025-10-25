/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:16:55 by miricci           #+#    #+#             */
/*   Updated: 2025/10/25 11:31:04 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**lst_to_array(t_list **head)
{
	t_list	*node;
	char	**array;
	int	i;

	i = 0;
	node = *head;
	array = (char **)malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	if (!array)
		return (NULL);
	while (node)
	{
		array[i] = (char *)malloc(sizeof(char) * ft_strlen(node->content));
		if (!array[i])
			return (NULL);
		ft_memcpy(array[i], node->content, ft_strlen(node->content));
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}