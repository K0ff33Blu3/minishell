/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:29:23 by miricci           #+#    #+#             */
/*   Updated: 2025/11/23 14:21:49 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_list **env_list, t_cmd *data)
{
	char	*target;

	if (array_size((void **)data->cmd_args) > 2)
		return (clean_data(data), write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!data->cmd_args[1])
		target = ft_getenv(env_list, "HOME");
	else
		target = ft_strdup(data->cmd_args[1]);
	if (!target)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (clean_data(data), 1);
	}
	if (chdir(target) == -1)
		return (clean_data(data), free(target), perror("minishell: cd"), 1);
	free(target);
	return (clean_data(data), 0);
}