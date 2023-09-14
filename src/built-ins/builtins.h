/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/14 20:38:07 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../inc/minishell.h"

void	ft_exit(t_shell *shell, t_cmd **cmd, int *i);

int 	compare_exit(char *argument);

int		env(char **envp);

int		pwd(char **envp);

int		echo(char **argv);

int		cd(t_shell *shell, t_cmd **cmd, int *i);

int		unset(t_shell *shell, t_cmd **cmd, int *i);

int		export(t_shell *shell, t_cmd **cmd, int *i);

int		export_n(char *var, t_shell *shell);

int		check_builtin(char **args);

int		run_builtin(t_shell *shell, int n);

int		is_digit(char c);

int		is_alpha(char c);

int		is_alpha_num(char c);

int		built_in(t_shell *shell, int n);

char 	*protect_quotes(char *var);

#endif
