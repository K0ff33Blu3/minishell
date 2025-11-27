/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:22:00 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:54:05 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char **token, int i)
{
	if (token[i])
	{
		if (!ft_strncmp(token[i], "<", 2) || !ft_strncmp(token[i], "<<", 3)
			|| !ft_strncmp(token[i], ">", 2) || !ft_strncmp(token[i], ">>", 3))
		{
			if (token[i + 1] && !is_metachar(token[i + 1]))
				return (EXIT_SUCCESS);
			else
				return (SYNT_ERR);
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	check_file_path(char *path, int perm_code)
{
	struct stat	st;

	if (!stat(path, &st))
	{
		if (!access(path, perm_code))
		{
			if (S_ISDIR(st.st_mode))
				return (IS_DIR);
			else
				return (EXIT_SUCCESS);
		}
		return (NO_PERM);
	}
	return (EXIT_FAILURE);
}

void	redirect(t_list **cmd, t_list **env, t_cmd *data)
{
	int	check;

	if (data->has_outfile && data->outfile)
	{
		check = check_file_path(data->outfile, W_OK);
		if (!check)
			ft_dup2(data->out_fd, STDOUT_FILENO);
		else
			ft_redir_err(env, cmd, data->outfile, check);
	}
	if (data->has_infile && data->infile)
	{
		check = check_file_path(data->infile, R_OK);
		if (!check)
			ft_dup2(data->in_fd, STDIN_FILENO);
		else
			ft_redir_err(env, cmd, data->infile, check);
	}
	else if (data->has_infile == 2)
		ft_dup2(data->tmp_pipe[0], STDIN_FILENO);
}
