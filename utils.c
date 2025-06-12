/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:05 by miricci           #+#    #+#             */
/*   Updated: 2025/06/12 15:14:09 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_cmdline *cmd)
{
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	is_emptystr(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	print_cmd_struct(t_cmdline cmd, int fd)
{
	int	i;

	i = -1;
	ft_putendl_fd("\nTOKEN", fd);
	while (cmd.token[++i])
	{
		ft_putstr_fd("token[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("]: ", fd);
		ft_putendl_fd(cmd.token[i], fd);
	}
	ft_putstr_fd("cmd: ", fd);
	ft_putendl_fd(cmd.cmd, fd);
	ft_putstr_fd("cmd_path: ", fd);
	ft_putendl_fd(cmd.cmd_path, fd);
	i = -1;
	ft_putendl_fd("\nCMD_ARG", fd);
	while (cmd.cmd_args[++i])
	{
		ft_putstr_fd("cmd_arg[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("]: ", fd);
		ft_putendl_fd(cmd.cmd_args[i], fd);
	}
	ft_putstr_fd("in_fd: ", fd);
	ft_putnbr_fd(cmd.in_fd, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("out_fd: ", fd);
	ft_putnbr_fd(cmd.out_fd, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("infile: ", fd);
	ft_putstr_fd(cmd.infile, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("outfile: ", fd);
	ft_putstr_fd(cmd.outfile, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n", fd);
}