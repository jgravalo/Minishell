/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/09 16:32:42 by dtome-pe         ###   ########.fr       */
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

int		pwd(t_shell *sh);

int		echo(char **argv);

int		cd(t_shell *sh, t_cmd **cmd, int i);

int		unset(t_shell *sh, t_cmd **cmd, int i);

int		export(t_shell *sh, t_cmd **cmd, int i);

int		export_n(char *var, t_shell *sh);

void	write_var(char *var, char **envp, int i);

char	*add_without_plus(char *var);

int		write_not_valid(char *var);

char	*cd_home(t_shell *sh, t_cmd **cmd, int i);

char	*cd_back(t_shell *sh, char *dir);

char	*cd_last(t_shell *sh, char *dir);

#endif
