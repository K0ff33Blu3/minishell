/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:52:47 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:44:53 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <stdlib.h>

# define PROMPT "\033[36mMINISHELL@ \033[0m"

// MACRO
# define NOT_FOUND 127
# define NO_PERM 126
# define IS_DIR 125
# define SYNT_ERR 2
# define IS_OUTPUT 100
# define IS_INPUT 101
# define BOTH 102

extern int	g_last_sig;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_cmd
{
	char	**token;
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
	int		in_fd;
	int		out_fd;
	char	*infile;
	char	*outfile;
	int		has_infile;
	int		has_outfile;
	int		tmp_pipe[2];
	int		pip[2];
}	t_cmd;

// command

// pwd.c
void	pwd(void);

// env.c
void	env(t_list **env_list);

// echo.c
void	echo(t_cmd *data);

// exit.c
int		exit_cmd(t_list **env_list, t_list **cmd_list, t_cmd *data);

// cd.c
int		ft_cd(t_list **env_list, t_cmd *data);

// unset.c
int		unset(t_list **env_list, char **var);

// export.c
int		export(t_list **cmd_list, t_list **env_list, t_cmd *data);
// export_helper.c
int		check_name(char	*name);
void	print_exp(t_list *node);
void	export_error(t_env *env_node, char *str);

// parsing.c
char	**parse_cmd_args(char **token, int *exit_status);
char	**get_cmd_token(char **all_token, int start, int end);
char	**token_parsing(t_list **env_list, char **token, int *exit_code);
t_cmd	*data_parsing(t_list **env_list, char **part_token, int *exit_status);

// quotes.c
char	**remove_quotes(char **str);

// expand.c
char	*expand_var(t_list **env_list, char *var, int exit_status);
char	*expand_str(t_list **env_list, char *str, int exit_status, int *i);
char	*expand_str_recursive(t_list **env_list, char *in_str, int exit_status);
char	*name_var(char *str);
char	**expand_env_var(t_list **env_list, char **token, int status);
// expand_helper.c
char	get_kind_of_quote(char *str);
int		find_dollar(char *str);

// token.c
int		count_token(char *s);
char	*make_word(char *s, int *j);
void	make_quote(char **word, char *s, int *j, int *i);
char	*make_metachar(char *s, int *j);
char	**tokenize(char *str);
// token_utils.c
int		skip_token(char *s, int i);
int		is_metachar(char *c);
int		skip_quote(char *s, int start);
int		word_len(char *s, unsigned int start);
int		quote_len(char *s, unsigned int start, char quote);

// signal.c
void	simple_handler(int signum);
void	waiting_signals(void);
void	setup_father(void);
void	check_signals(int status, int *exit_status);
// signal_helper.c
void	reset_signals(void);
void	ft_signum(int signum);
void	clean_sigint(t_cmd *cmd);

// redirections_in.c
void	get_line_heredoc(char *limiter);
int		handle_heredoc(t_cmd *cmd, char *limiter);
int		open_infile(t_cmd *cmd, int i, char **infile, int *last_fd);
int		handle_input_redir(t_cmd *cmd);

// redirections_out.c
int		open_outfile(t_cmd *cmd, int i, char **outfile, int *last_fd);
int		handle_output_redir(t_cmd *cmd);

// redirections.c
int		is_redir(char **token, int i);
int		check_file_path(char *path, int perm_code);
void	redirect(t_list **cmd, t_list **env, t_cmd *data);

// utils.c
char	**get_metachar(void);
int		is_emptystr(char *str);
char	*ft_getenv(t_list **env_list, char *name);
int		find_pipe(char **token, int *start);
void	ft_dup2(int dst_fd, int src_fd);

// find_cmd_path
char	*find_cmd_path(t_list **env_list, t_cmd *data);
int		check_cmd_path(char *path);

// pipe.c
void	close_pipe(int pip[2]);
void	handle_pipe(t_list **head, t_list *node);

// execution.c
void	exec_command(t_list **cmd_list, t_cmd *data, t_list **env_list);
void	exec_simple_builtin(t_list **cmd_lst, t_cmd *data, t_list **env_list);
void	exec_status_builtin(t_list **cmd, t_cmd *data, t_list **env, int *st);
int		is_builtin(char *cmd);
int		ft_single_builtin(t_list **cmd_list, t_list **env_list, int *status);

// cleaning.c
void	clean_data(void *ptr);
void	free_env(void *ptr);
void	ft_error(t_list **env_lst, t_list **cmd_lst, char *str, int exit_code);
void	ft_perror(char *str, int exit_code);
void	ft_redir_err(t_list **env, t_list **cmd, char *str, int code);

// closing.c
void	close_pipe(int pip[2]);
void	close_pipeline(t_list **cmd_list, t_list *cmd_node);
void	close_fd_parent(t_list **cmd, t_list *node);

// environment.c
char	**envlst_to_envp(t_list **head);
t_env	*mk_env(char *name, char *value);
char	*find_env_name(char *str);
char	*find_env_value(char *str);
int		update_env(t_list **env_list, t_env *new);

#endif