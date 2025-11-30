/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/11/30 19:16:32 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env_content(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

static	t_list	*sort_env_list(t_list *env)
{
	t_list	*i;
	t_list	*j;
	t_env	*env_i;
	t_env	*env_j;

	i = env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			env_i = (t_env *)i->content;
			env_j = (t_env *)j->content;
			if (ft_strncmp(env_i->name,
					env_j->name, ft_strlen(env_i->name) + 1) > 0)
				swap_env_content(i, j);
			j = j->next;
		}
		i = i->next;
	}
	return (env);
}

static int	export_one(t_list **env_list, char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (EXIT_FAILURE);
	new = mk_env(find_env_name(str), find_env_value(str));
	if (!check_name(new->name))
		return (export_error(new, str), EXIT_FAILURE);
	if (update_env(env_list, new))
		ft_lstadd_back(env_list, ft_lstnew(new));
	return (EXIT_SUCCESS);
}

static int	exp_no_args(t_list **cmd_list, t_cmd *cmd, t_list **env, int *st)
{
	t_list	*node;
	int		pid;
	int		status;

	setup_father();
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		reset_signals();
		redirect(cmd_list, env, cmd);
		sort_env_list(*env);
		node = *env;
		while (node)
		{
			print_exp(node);
			node = node->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	check_signals(status, st);
	return (status);
}

int	export(t_list **cmd_list, t_list **env_list, t_cmd *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	if (array_size((void **)data->cmd_args) == 1)
		return (exp_no_args(cmd_list, data, env_list, &status));
	while (data->cmd_args[++i])
		status = export_one(env_list, data->cmd_args[i]);
	return (status);
}
