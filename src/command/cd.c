/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:29:23 by miricci           #+#    #+#             */
/*   Updated: 2025/12/01 12:42:11 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_list **env_list, t_cmd *data)
{
	char	*target;
	t_env	*oldpwd;
	t_env	*pwd;

	if (array_size((void **)data->cmd_args) > 2)
		return (clean_data(data),
			ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!data->cmd_args[1])
		target = ft_getenv(env_list, "HOME");
	else
		target = ft_strdup(data->cmd_args[1]);
	if (!target)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (chdir(target) == -1)
		return (free(target), perror("cd"), 1);
	oldpwd = mk_env(ft_strdup("OLDPWD"), ft_getenv(env_list, "PWD"));
	pwd = mk_env(ft_strdup("PWD"), getcwd(NULL, 0));
	if (update_env(env_list, pwd))
		ft_lstadd_back(env_list, ft_lstnew(pwd));
	if (update_env(env_list, oldpwd))
		ft_lstadd_back(env_list, ft_lstnew(oldpwd));
	free(target);
	return (0);
}
