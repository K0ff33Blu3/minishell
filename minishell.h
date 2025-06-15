/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/06/15 21:34:37 by emondo           ###   ########.fr       */
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
	char	**all_cmd_lines;
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
	int	pip[2][2];
}	t_cmdline;

//echo_build.c

// build_in_cmd.c
void	pwd(void);
void	env(char **envp);
void	echo(t_cmdline *data);

// build_in_cmd_2.c
void	exit_cmd(t_cmdline *data);
int	ft_cd(t_cmdline *data);

// parsing.c
int	is_builtin(char *cmd);
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
void	handle_sigint_prompt(int signum);
void	setup_shell_signals(void);
void	reset_signals_default(void);

// redirections.c
int	handle_input_redir(t_cmdline *cmd);
int	handle_output_redir(t_cmdline *cmd);

// utils.c
void	print_cmd_struct(t_cmdline cmd, int fd);
int	is_emptystr(char *str);
void	ft_error(char *str);
char	**str_split(char *s, char c);

// find_cmd_path
void	cmd_not_found(t_cmdline *data);
char	*find_cmd_path(t_cmdline *data);

// execution.c
void	exec_command(t_cmdline *data, char **envp);
int	execute_builtin(t_cmdline *data);
void	one_cmd(t_cmdline *data, int fd, char **envp);

// pipe.c
void	piping(t_cmdline *data, int size, char **envp);
void	create_pipe(t_cmdline *data, int i, int size, char **envp);

// cleaning.c
void	free_cmdline(t_cmdline *data);
void	close_pipe(int pip[2][2]);


#endif