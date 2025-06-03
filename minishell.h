/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/05/30 11:04:03 by miricci          ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	char	*limiter;
	int	tmp_pipe[2];
	int	pipe[2];
	
}	t_cmdline;

// build_in_cmd.c
int	pwd(void);
int	env(char **envp);
int	echo(char *str, int n);

// parsing.c
void	pipe_parsing(char *cmd_line);
void	data_parsing(char *cmd_str, t_cmdline *data);

// expand.c
char	*expand_var_in_quotes(char *quote);
char	*expand_var(char *var);
char	*expanded_quote(char *quote);
char	**expand_env_var(char **token);
char	**expand_env_var(char **token);

// token.c
int	count_token(char *s);
char	*make_word(const char *s, int *j);
char	*make_quote(const char *s, int *j);
char	*make_metachar(const char *s, int *j);
char	**tokenize(char	*str);
char	**re_tokenize(char **arr, int size);

// token_utils.c
char	**get_metachar(void);
int	is_metachar(const char *c);
int	skip_quote(char *s, int start);
int	word_len(const char *s, unsigned int start);
int	quote_len(const char *s, unsigned int start, char quote);

// signal.c
void	ft_empty_handler(int signum);
void	ft_empty_initializer(void);

// redirections.c
int	handle_input_redir(t_cmdline *cmd);
int	handle_output_redir(t_cmdline *cmd);

// utils ??
void	print_cmd_struct(t_cmdline cmd);

#endif