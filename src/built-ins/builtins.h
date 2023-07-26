/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 16:22:50 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute, char **envp);

int	unset(char **var, char **envp);

int	export(char **args, char ***envp);

int	check_builtin(char **args, char **envp);

int	run_builtin(char **args, char **envp);

int is_digit(char c);

int is_alpha(char c);

int is_alpha_num(char c);

#endif
