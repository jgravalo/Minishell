/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:29:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 11:50:19 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*LISTS*/

/*tok*/

t_tok		*toknew(void *content);

int			tokback(t_tok **lst, t_tok *new);

t_tok		*toklast(t_tok *lst);

void		tokclear(t_tok **lst);

/* arg*/

t_arg		*argnew(void *content);

t_arg		*arglast(t_arg *lst);

int			argback(t_arg **lst, t_arg *new);

int			argsize(t_arg *lst);

void		argfront(t_arg **lst, t_arg *new);

void		argclear(t_arg **lst);

/*redir*/

t_redir		*redirnew(int type);

int			redirback(t_redir **lst, t_redir *new);

t_redir		*redirlast(t_redir *lst);

void		redclear(t_redir **lst);

/*quote*/

t_quote		*quotenew(int start, int end);

void		quoteback(t_quote **lst, t_quote *new);

t_quote		*quotelast(t_quote *lst);

/*string utils*/

int			ft_varcmp(const char *s1, const char *s2, size_t n);

/*printing utils*/

void		ft_printchararr(char **arr);

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

void		check_malloc_error(void *ptr);

int			count_exit_numbers(int n);

#endif
