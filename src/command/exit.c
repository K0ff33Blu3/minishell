/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:30:11 by miricci           #+#    #+#             */
/*   Updated: 2025/11/30 17:26:59 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int exit_cmd(t_list **env_list, t_list **cmd_list, t_cmd *data)
{
    int code;

    code = 0;
    if (array_size((void **)data->cmd_args) > 2)
        return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
    if (data && data->cmd_args && data->cmd_args[1])
    {
        if (!is_number(data->cmd_args[1]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(data->cmd_args[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            ft_lstclear(env_list, free_env);
            ft_lstclear(cmd_list, clean_data);
            exit(2);
        }
        code = ft_atoi(data->cmd_args[1]);
    }
    ft_lstclear(env_list, free_env);
    ft_lstclear(cmd_list, clean_data);
    printf("exit\n");
    return (exit(code), code);
}
