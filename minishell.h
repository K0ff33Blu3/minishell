/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/05/16 13:09:54 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[36mMINISHELL@ \033[0m"

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmdline
{
	char	*cmd_line;
	char	*cmd;
	char	**cmd_args;
	t_cmdline	*next;
}

int	pwd(void);
int	env(char **envp);
int	echo(char *str, int n);


#endif