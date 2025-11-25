/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:16:48 by miricci           #+#    #+#             */
/*   Updated: 2025/11/24 12:10:36 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_outfile(t_cmd *cmd, int i, char **outfile, int *last_fd)
{
	int	flag;
	
	flag = 0;
	free(*outfile);
	*outfile = ft_strdup(cmd->token[i + 1]);
	if (*last_fd > 1)
		close(*last_fd);
	if (!ft_strncmp(cmd->token[i], ">", 2))
	{
		*last_fd = open(*outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		flag = 1;
		if (*last_fd == -1)
			return (-1);
	}
	else if (!ft_strncmp(cmd->token[i], ">>", 3))
	{
		*last_fd = open(*outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (*last_fd == -1)
			return (-1);
		flag = 2;
	}
	return (flag);
}

int	handle_output_redir(t_cmd *cmd)
{
	int	i;
	char	*outfile;
	int	flag;
	int	last_fd;

	i = -1;
	flag = 0;
	last_fd = 1;
	outfile = NULL;
	while (cmd->token[++i])
	{
		if((!ft_strncmp(cmd->token[i], ">", 2) || !ft_strncmp(cmd->token[i], ">>", 3)) && cmd->token[i + 1])
			flag = open_outfile(cmd, i, &outfile, &last_fd);
	}
	if (flag)
		cmd->outfile = ft_strdup(outfile);
	else
		cmd->outfile = NULL;
	cmd->out_fd = last_fd;
	free(outfile);
	return (flag);
}
