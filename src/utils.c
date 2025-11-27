/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:05 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:25:17 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_metachar(void)
{
	static char	*metachar[18];

	metachar[0] = "||";
	metachar[1] = "&&";
	metachar[2] = "|";
	metachar[3] = "&";
	metachar[4] = "<<";
	metachar[5] = "<";
	metachar[6] = ">>";
	metachar[7] = ">";
	metachar[8] = "*";
	metachar[9] = "[";
	metachar[10] = "]";
	metachar[11] = "(";
	metachar[12] = ")";
	metachar[13] = "{";
	metachar[14] = "}";
	metachar[15] = "\\";
	metachar[16] = NULL;
	return (metachar);
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

char	*ft_getenv(t_list **env_list, char *name)
{
	t_list	*node;
	t_env	*env;
	int		name_len;

	node = *env_list;
	name_len = ft_strlen(name);
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(name, env->name, name_len))
			return (ft_strdup(env->value));
		node = node->next;
	}
	return (NULL);
}

int	find_pipe(char **token, int *start)
{
	int	end;

	if (!ft_strncmp(token[*start], "|", 2))
		(*start)++;
	end = *start;
	while (token[end] && ft_strncmp(token[end], "|", 2))
		end++;
	return (end);
}

void	ft_dup2(int dst_fd, int src_fd)
{
	dup2(dst_fd, src_fd);
	close(dst_fd);
}
