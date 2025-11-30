/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:05:20 by miricci           #+#    #+#             */
/*   Updated: 2025/11/30 19:29:13 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipeline(t_list **cmd_list, t_list *cmd_node)
{
	t_list	*node;

	node = *cmd_list;
	while (node)
	{
		if (node != cmd_node)
			close_pipe(((t_cmd *)(node->content))->pip);
		node = node->next;
	}
}

void	close_fd_parent(t_list **cmd, t_list *node)
{
	int		node_i;
	t_cmd	*data;
	t_cmd	*data_nxt;

	node_i = ft_lstindex(*cmd, node);
	data = (t_cmd *)node->content;
	if (node->next)
		data_nxt = (t_cmd *)((node->next)->content);
	else
		data_nxt = NULL;
	if (node_i < 0)
		return ;
	if (node_i > 0)
		close(data->pip[0]);
	if (node_i < ft_lstsize(*cmd) - 1)
		close(data_nxt->pip[1]);
	if (data->has_infile && data->in_fd > 2)
		close(data->in_fd);
	if (data->has_outfile && data->out_fd > 2)
		close(data->out_fd);
}
