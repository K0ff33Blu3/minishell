/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:05 by miricci           #+#    #+#             */
/*   Updated: 2025/11/25 17:21:55 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envlst_to_envp(t_list **head)
{
	t_list	*node;
	char	*tmp;
	char	**array;
	int	i;

	i = 0;
	node = *head;
	array = (char **)malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	if (!array)
		return (NULL);
	while (node)
	{
		if (((t_env *)node->content)->value)
		{
			tmp = ft_strjoin(((t_env *)node->content)->name, "=");
			array[i] = ft_strjoin(tmp, ((t_env *)node->content)->value);
			free(tmp);
		}
		else
			array[i] = ft_strdup(((t_env *)node->content)->name);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
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

// void	print_cmd_struct(t_cmd cmd, int fd)
// {
// 	int	i;

// 	i = -1;
// 	ft_putendl_fd("\nTOKEN", fd);
// 	while (cmd.token[++i])
// 	{
// 		ft_putstr_fd("token[", fd);
// 		ft_putnbr_fd(i, fd);
// 		ft_putstr_fd("]: ", fd);
// 		ft_putendl_fd(cmd.token[i], fd);
// 	}
// 	ft_putstr_fd("cmd: ", fd);
// 	ft_putendl_fd(cmd.cmd, fd);
// 	if (!is_builtin(cmd.cmd))
// 	{
// 		ft_putstr_fd("cmd_path: ", fd);
// 		ft_putendl_fd(cmd.cmd_path, fd);
// 	}
// 	i = -1;
// 	ft_putendl_fd("\nCMD_ARG", fd);
// 	while (cmd.cmd_args[++i])
// 	{
// 		ft_putstr_fd("cmd_arg[", fd);
// 		ft_putnbr_fd(i, fd);
// 		ft_putstr_fd("]: ", fd);
// 		ft_putendl_fd(cmd.cmd_args[i], fd);
// 	}
// 	ft_putstr_fd("in_fd: ", fd);
// 	ft_putnbr_fd(cmd.in_fd, fd);
// 	ft_putstr_fd("\n", fd);
// 	ft_putstr_fd("out_fd: ", fd);
// 	ft_putnbr_fd(cmd.out_fd, fd);
// 	ft_putstr_fd("\n", fd);
// 	ft_putstr_fd("infile: ", fd);
// 	ft_putstr_fd(cmd.infile, fd);
// 	ft_putstr_fd("\n", fd);
// 	ft_putstr_fd("outfile: ", fd);
// 	ft_putstr_fd(cmd.outfile, fd);
// 	ft_putstr_fd("\n", fd);
// 	ft_putstr_fd("\n", fd);
// }

t_env	*mk_env2(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (!value)
	{
		env->name = ft_strdup(name);
		env->value = NULL;
		return (env);
	}
	env->name = ft_strdup(name);
	if (!*value)
	{
		env->value = ft_strdup("");
		return (env);
	}
	env->value = ft_strdup(value);
	// free(value);
	// free(name);
	return (env);
}

char	*find_env_name(char *str)
{
	int	len;
	
	len = ft_indchr(str, '=');
	if (len == -1)
		return (ft_strdup(str));
	return (ft_substr(str, 0 , len));
}

char	*find_env_value(char *str)
{
	int	len;
	int	name_len;

	name_len = ft_indchr(str, '=');
	if (name_len == -1)
		return (NULL);
	len = ft_strlen(str) - name_len - 1;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_substr(str, name_len + 1, len));
}

t_env	*mk_env(char *str)
{
	t_env	*env;
	int	value_len;
	int	name_len;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	name_len = ft_indchr(str, '=');
	if (name_len < 0)
	{
		env->name = ft_strdup(str);
		env->value = NULL;
		return (env);
	}
	env->name = ft_substr(str, 0 , name_len);
	value_len = ft_strlen(str) - name_len - 1;
	if (value_len == 0)
	{
		env->value = ft_strdup("");
		return (env);
	}
	env->value = ft_substr(str, ft_indchr(str, '=') + 1, value_len);
	return (env);
}

t_list	**env_init(char **envp)
{
	t_list	**env_list;
	t_list	*node;

	env_list = (t_list **) malloc (sizeof(t_list *));
	if (!env_list)
		return (NULL);
	*env_list = ft_lstnew(mk_env2(find_env_name(*envp), find_env_value(*envp)));
	envp++;
	while (*envp)
	{
		node = ft_lstnew(mk_env2(find_env_name(*envp), find_env_value(*envp)));
		ft_lstadd_back(env_list, node);
		envp++;
	}
	return (env_list);
}

char	*ft_getenv(t_list **env_list, char *name)
{
	t_list	*node;
	t_env	*env;
	int	name_len;

	node = *env_list;
	name_len = ft_strlen(name);
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(name, env->name, name_len))
			return(ft_strdup(env->value));
		node = node->next;
	}
	return (NULL);
}

int	update_env(t_list **env_list, t_env *new)
{
	t_list	*node;
	t_env	*env;
	
	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(new->name, env->name, ft_strlen(new->name) + 1))
		{
			free(env->value);
			env->value = ft_strdup(new->value);
			free_env(new);
			return (EXIT_SUCCESS);
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}