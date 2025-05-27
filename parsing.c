/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/05/18 12:09:24 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdline *data_parsing(char *cmd_str)
{
	char	*trimmed;
	t_cmdline	*data;
	
	data = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!data)
		return (NULL);
	trimmed = ft_strtrim(cmd_str, " ");
	if (!trimmed)
		return (NULL); 
	data->cmd_line = ft_strdup(trimmed);
	printf("%s\n", data->cmd_line);
	free(trimmed);
	return (data);
}

t_list	**pipe_parsing(char *cmd_line)
{
	t_cmdline	*data;
	t_list		**head;
	t_list		*node;
	char	**splitted_cmd_line;
	int	i;

	i = 0;
	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	*head = NULL;
	splitted_cmd_line = ft_split(cmd_line, '|');
	if (!splitted_cmd_line)
		return (NULL);
	while (splitted_cmd_line[i])
	{
		data = data_parsing(splitted_cmd_line[i]);
		node = ft_lstnew((void *)data);
		if (!node)
			return (NULL);
		ft_lstadd_back(head, node);
		i++;		
	}
	ft_free((void **)splitted_cmd_line, -1);
	return (head);
}
