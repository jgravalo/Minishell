/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:22:39 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_exit(t_shell *shell, t_cmd **cmd, int i);

int		compare_exit(char *argument);

int		env(char **envp);

int		pwd(char **envp);

int		echo(char **argv);

int		cd(t_shell *shell, t_cmd **cmd, int i);

int		unset(t_shell *shell, t_cmd **cmd, int i);

int		export(t_shell *shell, t_cmd **cmd, int i);

int		export_n(char *var, t_shell *shell);

int		run_builtin(t_shell *shell, int n);

int		built_in(t_shell *shell, int n);

int		write_not_valid(char *var);

#endif
