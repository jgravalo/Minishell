/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:45:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 21:22:52 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include <fcntl.h>
//# include <defines.h>
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
//# include "../gnl/get_next_line.h"
//# include "builtins.h"

# define IN 1
# define OUT 2
# define APPEND 3
# define HERE 4

# define DEF_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"
# define INFILE shell->struct_cmd[n]->redir[i]->type == 0
# define HEREDOC shell->struct_cmd[n]->redir[i]->type == 1
# define OUTFILE shell->struct_cmd[n]->redir[i]->type == 2
# define OUTFILE_APPEND shell->struct_cmd[n]->redir[i]->type == 3
# define READ 0
# define WRITE 1

typedef struct s_hist{
	char			*line;
	struct s_hist	*next;
	struct s_hist	*ant;
}	t_hist;

typedef struct s_pipe{
	int	p[2];
	int	fdin;
	int	fdout;
//	struct s_pipe	*next;
}	t_pipe;

typedef struct s_arg
{
	char *arg;
	char *quoted_str;
	int	 quoted;
	struct s_arg 	*next;
}				t_arg;

typedef struct s_redir
{
	t_arg 	*arg;
	char	*path;
	int 	heredoc_quoted;
	int		heredoc_fd;
	int		fd;
	int		type;
	struct s_redir	*next;
}			t_redir;


extern int	g_exit;

typedef struct s_quote
{
	int	start;
	int end;
	struct s_quote	*next;
}				t_quote;

typedef	struct s_cmd
{
	char **args;
	t_arg 	*arg;
	t_arg	*arg_x;
	t_redir *red;
	t_redir	*red_x;
	char	*path;
	char	*infile_path;
	char	*outfile_path;
	int		in_pipe;
	int		out_pipe;
	int		here_doc;
	int		builtin;
	int		in_fd;
	int 	out_fd;
	pid_t	pid;
}				t_cmd;

typedef struct s_token
{
	char	*tok;
	char	*type;
	struct s_token	*next;
}				t_tok;

typedef struct s_shell
{
	t_tok	*tok;
	t_tok	*expanded;
	t_quote	*quote;
	char	*tmp;
	char 	**envp;
	char	**args;
	char	*here_tmp;
	char	*readline;
	char	*prompt;
	t_pipe	*p;
	t_pipe	*p_err;
	pid_t	*pid;
	int		*pid_end;
	t_cmd	**struct_cmd;
	t_cmd	**s_cmd;
	char	*cmd;
	char	*user;
	char 	*delimiter;
	char 	*error_tmp;
	char 	*old_pwd;
	int		*redir_error;
	int		next_redir;
	int		var_quoted;
	int		var_cat;
	int		line_number;
	int		heredoc_quoted;
	int		redir_type;
	int		infd;
	int		outfd;
	int		stdin_cpy;
	int		stdout_cpy;
	int		*inpipe;
	int		*outpipe;
	int		pipes;
	int		exit;
	int		children;
	int		last_builtin;
	int		i;
	//
	int		*vars_loc;
	char	**vars_exp;
	char 	*last_arg;
}			t_shell;


# include "../src/built-ins/builtins.h"

typedef struct s_var
{
	char	**tmp;
	char	*new;
	char	*exp;
	char	*var;
	char	*c;
}	t_var;

int		cmd_error(char *s, int n, int exit);

size_t	ft_strlen(const char *str);

int		ft_strcmp(char *s1, char *s2);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_varcmp(const char *s1, const char *s2, size_t n);

char	*ft_strchr(char *str, int c);

char	*ft_strcat(char *dest, char *src);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_strdup(char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

void	ft_printarr(char **arr);

char	**ft_split(char const *s, char c);

char	**ft_split_double(char const *s, char c);

char	**ft_split_marks(char const *s, char c);

void	free_m(char **fdf);

char	*search_var_line(char *name, char **envp);

int		search_var_num(char *name, char **envp);

int		is_existing(char *line, char **envp);

char	*check_vars(char *args, char **envp);

char	*file_cmd(t_shell *shell, int n);

char 	*parse_redir(char *line, t_shell *shell, int n);

int		count_ascii(char *line, int c);

int		count_arr(char **args);

int		new_shell(t_shell *shell);

void	parse_pipex(t_shell *shell);

void 	lexer(t_shell *shell, char *line);

int		count_tokens(char *line);

int		is_pipe(char c);

int		is_redir(char *str);

char 	*parse_heredoc(char *line, t_shell *shell, int n);

char	**ft_split_heredoc(char *line);

int		is_meta(char c);

char	*expand_meta(t_shell *shell, char *line, int heredoc);

char	*c_str(char const *s, char c, int *n);

int		words(const char *s, char c);

int		is_local(char *cmd);

void 	parent_close(t_shell *shell);

void 	parent_close_but_one(t_shell *shell);

void 	close_fd(t_shell *shell, int i);

//void 	create_pipes(t_shell *shell);

char 	*get_prompt(t_shell *shell, char **envp);

char	*prompt_join(char *s1, char *s2);

char	*parse_quotes(char *s);

int		*parse_pipes(t_shell *shell);

void	make_redir(t_shell *shell, int n);

char		*ft_itoa(int n);

int64_t		ft_atoi(char *str);

uint64_t	ft_u_atoi(char *str);

void	parent_routine(t_shell *shell, int i);

void	child_routine(t_shell *shell, int i);

void	empty_old_pwd(t_shell *shell);

void	alloc_envp(t_shell *shell, char **envp);

int		new_shell(t_shell *shell);

void	wait_for_children(t_shell *shell);

void 	init_shell(t_shell *shell);

int		change_var(t_shell *shell, char *var, char *content);

void	parse_no_pipes_line(t_shell *shell);

void	set_signals(t_shell *shell, char **envp);

void	parse_line(t_shell *shell, int i);

void 	cmd_not_found(char *cmd);

int 	is_there_redir(char *line);

int		make_stdin_stdout(t_shell *shell, int n);

int		prepare_redir(char *line, t_shell *shell, int n, int redir_num);

char	*get_redir(char *line);

char	*remove_quotes(t_shell *shell, char *str);

int 	count_len_quotes(char *str);

int		count_redir(char *line);

int		len_redir(char *line);

int 	is_there_dollar(char *line, char c);

int 	check_for_tilde(char *line);

int		words_meta(const char *s, char c);

int 	search_dollar(char const *s, char c);

char	*meta_str(char const *s, char c, int *n);

void 	set_redir(t_shell *shell, int n);

int		count_redir_arr(char **args);

void	ft_print_intarr(int *arr, int n);

int		dir_error(char *s, int n, int exit);

char 	*remove_backslash(char *s);

void 	expander(t_shell *shell, t_cmd **cmd);

void	ft_printlst(t_tok *lst);

char 	*expand_str(t_shell *shell, t_arg *arg, int *i, int *j);

int		is_alpha_num_exp(char c);

int 	count_expstr(t_shell *shell, char *str, int *i);

void 	parser(t_shell *shell);

void 	categorizer(t_tok *expanded);

void	ft_printbothlst(t_tok *lst);

void	ft_printcmd(t_cmd **cmd);

void	ft_printredirlist(t_redir *redir);

void	ft_printarglist(t_arg *arg);

void	ft_printredirarglist(t_arg *arg);

void	ft_printcmdargx(t_cmd **cmd);

void 	quote_remove(t_cmd **cmd);

void 	execute(t_shell *shell, t_cmd **cmd);

int 	execute_redir(t_shell *shell, t_cmd **cmd, int *i);

void 	heredoc(t_shell *shell, t_cmd **cmd, int *i);

int 	builtin(t_shell *shell, t_cmd **cmd, int *i);

void 	ft_printdeflist(t_cmd **cmd);

void	set_argv(t_cmd **cmd);

void	search(t_shell *shell, t_cmd **cmd, int *i);

void	filedir_not_found(char *cmd);

void 	execute_pipes(t_shell *shell, t_cmd **cmd, int i);

void	parent_wait(t_shell *shell, t_cmd **cmd);

int 	check_builtin(char **args);

int 	count_quotes(t_shell *shell, char *str);

void 	copy_new(t_shell *shell, char *new, char *str);

void 	expand_args(t_shell *shell, t_cmd **cmd);

void 	expand_redir(t_shell *shell, t_cmd **cmd);

int 	count_expand(t_shell *shell, char *token, int *len);

void	copy_exp(char *dst, const char *src, int *cpy, size_t dstsize);

void	*ft_memset(void *b, int c, size_t n);

int	get_len(char *line, int *len, int *cpy);

void	move_ptrs(int *i, int *j);

/*tok lists*/

t_tok	*toknew(void *content);

void	tokback(t_tok **lst, t_tok *new);

t_tok	*toklast(t_tok *lst);

/* arg lists */

t_arg	*argnew(void *content);

t_arg	*arglast(t_arg *lst);

void	argback(t_arg **lst, t_arg *new);

int		argsize(t_arg *lst);

void	argfront(t_arg **lst, t_arg *new);

/*redir lists*/

t_redir	*redirnew(int type);

void	redirback(t_redir **lst, t_redir *new);

t_redir	*redirlast(t_redir *lst);

/*quote lists*/

t_quote	*quotenew(int start, int end);

void	quoteback(t_quote **lst, t_quote *new);

t_quote	*quotelast(t_quote *lst);

/*aux expander*/

void	init_variables_loop(int *i, int *len, int *cpy, int *size);

void	init_variables(int *i, int *j, int *n, t_shell *sh);

void	advance_space(char *str, int *len, int *cpy);

void	check_quoted(t_shell *sh, int *len);

void	copy_and_remove_quotes(t_shell *sh, int size, char *str, int *cpy);

#endif
