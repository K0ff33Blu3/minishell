/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:29:23 by miricci           #+#    #+#             */
/*   Updated: 2025/11/25 17:11:57 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_list **env_list, t_cmd *data)
{
	char	*target;
	t_env	*oldpwd;
	t_env	*pwd;

	if (array_size((void **)data->cmd_args) > 2)
		return (clean_data(data), write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!data->cmd_args[1])
		target = ft_getenv(env_list, "HOME");
	else
		target = ft_strdup(data->cmd_args[1]);
	if (!target)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), clean_data(data), 1);
	if (chdir(target) == -1)
		return (clean_data(data), free(target), perror("minishell: cd"), 1);
	oldpwd = mk_env2("OLDPWD", ft_getenv(env_list, "PWD"));
	pwd = mk_env2("PWD", getcwd(NULL, 0));
	if(!update_env(env_list, pwd))
		ft_lstadd_back(env_list, ft_lstnew(pwd));
	if(!update_env(env_list, oldpwd))
		ft_lstadd_back(env_list, ft_lstnew(oldpwd));		
	free(target);
	return (clean_data(data), 0);
}
