/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/11 21:55:07 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_builtin(char **args)
{
	if (!args)
		return (0);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	else
		return (0);
}

int	run_builtin(t_shell *shell, int n)
{
	if (ft_strcmp(shell->struct_cmd[n]->args[0], "cd") == 0)
		shell->exit = cd(shell, n);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "echo") == 0)
		shell->exit = echo(shell->struct_cmd[n]->args);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "env") == 0)
		shell->exit = env(shell->envp);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "export") == 0)
		shell->exit = export(shell, n);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "pwd") == 0)
		shell->exit = pwd(shell->envp);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "unset") == 0)
		shell->exit = unset(shell, n);
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], "exit") == 0)
		ft_exit(shell, n);
	return (shell->exit);
}

int	built_in(t_shell *shell, int n)
{
	if (check_builtin(shell->struct_cmd[n]->args) == 1)
	{
		if (shell->struct_cmd[n]->infile > -1
			|| shell->struct_cmd[n]->outfile > -1)
			make_redir(shell, n);
		run_builtin(shell, n);
		return (1);
	}
	else
		return (0);
}
