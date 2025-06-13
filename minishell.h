/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/06/13 11:27:37 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# define PROMPT "\033[36mMINISHELL@ \033[0m"

// MACRO
# define CMD_NOT_FOUND 127

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
	int	has_infile;
	int	has_outfile;
	int	tmp_pipe[2];
	int	pipe[2];
	
}	t_cmdline;
//execute_builtin
int	execute_builtin(t_cmdline *data);
//echo_build.c
int	echo_builtin(t_cmdline *data);

// build_in_cmd.c
int	pwd(void);
int	env(char **envp);
int	echo(char *str, int n);

// parsing.c
char	**remove_quotes(char **str); 
char	**get_data_token(char *str);
t_cmdline	*data_init(void);
char	**parse_cmd_args(char **token);
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

// utils.c
void	print_cmd_struct(t_cmdline cmd, int fd);
int	is_emptystr(char *str);
void	close_pipe(t_cmdline *cmd);
void	ft_error(char *str);

// find_cmd_path
void	cmd_not_found(t_cmdline *data);
char	*find_cmd_path(t_cmdline *data);

// execution.c
void	exec_command(t_cmdline *data, char **envp);
void	one_cmd(char *cmd_line, int fd, char **envp);

// pipe.c
void	piping(char **cmd_line, int size, char **envp);
void	create_pipe(char *cmd_line, int i, int size, char **envp, int (*pip)[2]);

#endif