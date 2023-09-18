/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:45:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 12:24:24 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdint.h>
# include <dirent.h>

# define IN 1
# define OUT 2
# define APPEND 3
# define HERE 4

# define DEF_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"
# define READ 0
# define WRITE 1

typedef struct s_pipe{
	int	p[2];
	int	fdin;
	int	fdout;
}	t_pipe;

typedef struct s_arg
{
	char			*arg;
	struct s_arg	*next;
}				t_arg;

typedef struct s_redir
{
	t_arg			*arg;
	char			*path;
	int				heredoc_quoted;
	int				heredoc_fd;
	int				fd;
	int				type;
	struct s_redir	*next;
}			t_redir;

extern int	g_exit;

typedef struct s_quote
{
	int				start;
	int				end;
	struct s_quote	*next;
}				t_quote;

typedef struct s_cmd
{
	char	**args;
	t_arg	*arg;
	t_arg	*arg_x;
	t_redir	*red;
	t_redir	*red_x;
	char	*path;
	int		in_pipe;
	int		out_pipe;
	int		in_fd;
	int		out_fd;
	pid_t	pid;
}				t_cmd;

typedef struct s_token
{
	char			*tok;
	char			*type;
	struct s_token	*next;
}				t_tok;

typedef struct s_shell
{
	char	**envp;
	char	**args;
	t_cmd	**s_cmd;
	t_tok	*tok;
	t_quote	*quote;
	t_pipe	*p;
	char	*tmp;
	char	*here_tmp;
	char	*readline;
	char	*user;
	char	*old_pwd;
	char	*last_arg;
	char	*pwd;
	int		cd_last;
	int		pwd_set;
	int		next_redir;
	int		var_quoted;
	int		var_cat;
	int		line_number;
	int		heredoc_quoted;
	int		stdin_cpy;
	int		stdout_cpy;
	int		pipes;
	int		exit;
	int		children;
}			t_shell;

/*MAINS*/

int		new_shell(t_shell *shell);

int     parse_pipes(t_shell *shell);

void	lexer(t_shell *shell, char *line);

void	categorizer(t_tok *expanded);

void	expander(t_shell *shell, t_cmd **cmd);

void	parser(t_shell *shell);

void	execute(t_shell *shell, t_cmd **cmd);

int		builtin(t_shell *shell, t_cmd **cmd, int i);

void	search(t_shell *shell, t_cmd **cmd, int i);

/*LEXER*/

int		count_tokens(char *line);

int		get_len(char *line, int *len);

int		cmd_error(char *s, int n, int exit);

char	*search_var_line(char *name, char **envp);

int		search_var_num(char *name, char **envp);

int		is_existing(char *line, char **envp);

int		is_pipe(char c);

int		is_redir(char *str);

int		is_meta(char c);

int		words(const char *s, char c);

void	parent_close(t_shell *shell);

void	parent_close_but_one(t_shell *shell);

void	create_pipes(t_shell *sh);

void	empty_old_pwd(t_shell *shell);

void	alloc_envp(t_shell *shell, char **envp);

int		new_shell(t_shell *shell);

int		change_var(t_shell *shell, char *var, char *content);

void	cmd_not_found(char *cmd);

char	*remove_quotes(t_shell *shell, char *str);

int		dir_error(char *s, int n, int exit);

char	*expand_str(t_shell *shell, t_arg *arg, int *i, int *j);

int		is_alpha_num_exp(char c);

int		execute_redir(t_shell *shell, t_cmd **cmd, int i);

void	set_argv(t_cmd **cmd);

void	filedir_not_found(char *cmd);

void	execute_pipes(t_shell *shell, t_cmd **cmd, int i);

void	parent_wait(t_shell *shell, t_cmd **cmd);

int		check_builtin(char **args);

int		count_quotes(t_shell *shell, char *str);

void	copy_new(t_shell *shell, char *new, char *str);

char	*get_var(char *str, int *i);

/*EXPANDER*/

int		count_expstr(t_shell *shell, char *str, int *i);

void	expand_args(t_shell *shell, t_cmd **cmd);

void	expand_redir(t_shell *shell, t_cmd **cmd);

int		count_expand(t_shell *shell, char *token, int *len);

void	copy_exp(char *dst, const char *src, int *cpy, size_t dstsize);

void	init_variables_loop(int *i, int *len, int *cpy, int *size);

void	init_variables(int *i, int *j, int *n, t_shell *sh);

void	advance_space(char *str, int *len, int *cpy);

void	check_quoted(t_shell *sh, int *len);

void	copy_and_remove_quotes(t_shell *sh, int size, char *str, int *cpy);

/*HEREDOC*/

void	heredoc(t_shell *shell, t_cmd **cmd);

void	exit_heredoc(int sig);

void	parent_heredoc(int sig);

void	write_heredoc_eof(t_shell *shell, int start_line, char *delimiter);

/*ERRORS*/

void	access_dir(void);

int		args_error(void);

#endif
