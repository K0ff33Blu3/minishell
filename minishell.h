/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/05/28 11:11:10 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>

# define PROMPT "\033[36mMINISHELL@ \033[0m"

extern int	g_last_sig;

typedef struct s_cmdline
{
	char	**token;
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
	int	in_fd;
	int	out_fd;
	
}	t_cmdline;

// build_in_cmd.c
int	pwd(void);
int	env(char **envp);
int	echo(char *str, int n);

// parsing.c
t_list	**pipe_parsing(char *cmd_line);

// token.c
int	count_token(char *s);
char	*make_word(const char *s, int *j);
char	*make_quote(const char *s, int *j);
char	*make_metachar(const char *s, int *j);
char	**tokenize(char	*str);

// token_utils.c
char	**get_metachar(void);
int	is_metachar(const char *c);
int	skip_quote(char *s, int start);
int	word_len(const char *s, unsigned int start);
int	quote_len(const char *s, unsigned int start, char quote);

// signal.c
void	ft_empty_handler(int signum);
void	ft_empty_initializer(void);
void	ignore_sigquit(void);
void	ignore_sigtstp(void);

#endif