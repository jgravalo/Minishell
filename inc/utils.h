/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:29:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 10:07:51 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*LISTS*/

/*tok*/

t_tok		*toknew(void *content);

void		tokback(t_tok **lst, t_tok *new);

t_tok		*toklast(t_tok *lst);

/* arg*/

t_arg		*argnew(void *content);

t_arg		*arglast(t_arg *lst);

void		argback(t_arg **lst, t_arg *new);

int			argsize(t_arg *lst);

void		argfront(t_arg **lst, t_arg *new);

/*redir*/

t_redir		*redirnew(int type);

void		redirback(t_redir **lst, t_redir *new);

t_redir		*redirlast(t_redir *lst);

/*quote*/

t_quote		*quotenew(int start, int end);

void		quoteback(t_quote **lst, t_quote *new);

t_quote		*quotelast(t_quote *lst);

/*string utils*/

size_t		ft_strlen(const char *str);

int			ft_strcmp(char *s1, char *s2);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_varcmp(const char *s1, const char *s2, size_t n);

char		*ft_strchr(char *str, int c);

char		*ft_strcat(char *dest, char *src);

char		*ft_strjoin(char *s1, char *s2);

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

char		*ft_strdup(char *str);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

int64_t		ft_atoi(char *str);

uint64_t	ft_u_atoi(char *str);

/*printing utils*/

void		ft_printarr(char **arr);

void		ft_printlst(t_tok *lst);

void		ft_print_intarr(int *arr, int n);

void		ft_printdeflist(t_cmd **cmd);

void		ft_printbothlst(t_tok *lst);

void		ft_printcmd(t_cmd **cmd);

void		ft_printredirlist(t_redir *redir);

void		ft_printarglist(t_arg *arg);

void		ft_printredirarglist(t_arg *arg);

void		ft_printcmdargx(t_cmd **cmd);

/*others*/

void		*ft_memset(void *b, int c, size_t n);

void		move_ptrs(int *i, int *j);

int			count_arr(char **args);

void		free_m(char **fdf);

int			is_digit(char c);

int			is_alpha(char c);

int			is_alpha_num(char c);

#endif
