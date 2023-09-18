/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 11:10:44 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_exit(t_shell *sh, t_cmd **cmd, int i);

void	ft_unset(t_shell *sh, char *var);

void	ft_export(t_shell *sh, char *var);

int		compare_exit(char *argument);

int		env(char **envp);

int		pwd(char **envp);

int		echo(char **argv);

int		cd(t_shell *sh, t_cmd **cmd, int i);

int		unset(t_shell *sh, t_cmd **cmd, int i);

int		export(t_shell *sh, t_cmd **cmd, int i);

int		export_n(char *var, t_shell *sh);

int		run_builtin(t_shell *sh, int n);

int		built_in(t_shell *sh, int n);

int		write_not_valid(char *var);

/*cd*/

char	*cd_home(t_shell *sh, t_cmd **cmd, int i);

char	*cd_back(t_shell *sh, t_cmd **cmd, int i);

char	*cd_last(t_shell *sh, t_cmd **cmd, int i);

#endif
