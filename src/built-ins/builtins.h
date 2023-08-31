/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/31 16:29:49 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../inc/minishell.h"

void	ft_exit(t_shell *shell, int n);

int		env(char **envp);

int		pwd(char **envp);

int		echo(char **argv);

int		cd(t_shell *shell, int n);

int		unset(t_shell *shell, int n);

int		export(t_shell *shell, int n);

int		export_n(char *var, t_shell *shell);

int		check_builtin(char **args);

int		run_builtin(t_shell *shell, int n);

int		is_digit(char c);

int		is_alpha(char c);

int		is_alpha_num(char c);

int		built_in(t_shell *shell, int n);

#endif
