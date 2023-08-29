/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:45:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/29 11:38:15 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define DEF_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"
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

typedef	struct s_cmd
{
	char **args;
	int		infile;
	int 	outfile;

}				t_cmd;

typedef struct s_shell
{
	char	**tokens;
	char	**pipes;
	char 	**envp;
	char	**args;
	char	*here_tmp;
	char	*readline;
	char	*prompt;
	t_pipe	*p;
	t_pipe	*p_err;
	pid_t	*pid;
	int		*pid_end;
	t_cmd	*struct_cmd;
	char	*cmd;
	char	*user;
	char 	*delimiter;
	int		line_number;
	int		heredoc_quoted;
	int		redir_type;
	int		infd;
	int		outfd;
	int		saved_stdin;
	int		saved_stdout;
	int		inpipe;
	int		outpipe;
	int		pipex;
	int		exit;
	int		children;
	int		last_builtin;
	int		i;
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

char	*file_cmd(t_shell *shell);

char 	*parse_redir(char *line, t_shell *shell);

int		count_ascii(char *line, int c);

int		count_arr(char **args);

int		new_shell(t_shell *shell);

void	parse_pipex(t_shell *shell);

char	**lexer(char *line);

int		count_tokens(char *line);

int		is_pipe_or_dollar(char c);

int		is_redir(char *str);

char	*parse_heredoc(char *line);

int		is_meta(char c);

char	*expand_meta(t_shell *shell, char **envp);

char	*c_str(char const *s, char c, int *n);

int		words(const char *s, char c);

int		is_local(char *cmd);

void 	parent_close(t_shell *shell);

void 	parent_close_but_one(t_shell *shell);

void 	close_fd(t_shell *shell, int i);

void 	create_pipes(t_shell *shell);

void	check_pipe(t_shell *shell, int i);

char 	*get_prompt(t_shell *shell, char **envp);

char	*prompt_join(char *s1, char *s2);

char	*parse_quotes(char *s);

void	make_redir(t_shell *shell);

int 	recover_std(t_shell *shell);

char	*ft_itoa(int n);

int64_t	ft_atoi(char *str);

uint64_t	ft_u_atoi(char *str);

void	parent_routine(t_shell *shell, int i);

void	child_routine(t_shell *shell, int i);

void	empty_old_pwd(t_shell *shell);

void	alloc_envp(t_shell *shell, char **envp);

int		new_shell(t_shell *shell);

void	wait_for_children(t_shell *shell);

void 	init_shell(t_shell *shell);


void	parse_no_pipes_line(t_shell *shell);


void	set_signals(t_shell *shell, char **envp);

void	parse_line(t_shell *shell, int i);

int 	cmd_not_found(char *cmd);

int 	is_there_redir(char *line);

void 	write_heredoc_eof(t_shell *shell, int start_line);

int		make_stdin_stdout(t_shell *shell);

void	prepare_redir(char *line, t_shell *shell);

char	*get_redir(char *line);

char	*remove_quotes(char *str);

int 	count_len_quotes(char *str);

int		count_redir(char *line);

int		len_redir(char *line);
/*
void	make_history(t_hist *hist, char *line);

void	print_history(t_hist *hist);

void	free_history(t_hist *hist);
*/
#endif
