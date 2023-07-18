/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:03:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/18 22:44:43 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute, char **envp);

int	unset(char **var, char ***envp);

int	export(char **args, char ***envp);

int	run_cd(char **args, char **envp);

int	run_builtin(char **args, char **envp);

int is_digit(char c);

int is_alpha(char c);

int is_alpha_num(char c);

#endif
