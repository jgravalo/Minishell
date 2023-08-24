/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 12:03:36 by theonewhokn      ###   ########.fr       */
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
		return(1);
	else
		return (0);
}

int	run_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->args[0], "cd") == 0)
		shell->exit = cd(shell);
	else if (ft_strcmp(shell->args[0], "echo") == 0)
		shell->exit = echo(shell->args);
	else if (ft_strcmp(shell->args[0], "env") == 0)
		shell->exit = env(shell->envp);
	else if (ft_strcmp(shell->args[0], "export") == 0)
		shell->exit = export(shell);
	else if (ft_strcmp(shell->args[0], "pwd") == 0)
		shell->exit = pwd(shell->envp);
	else if (ft_strcmp(shell->args[0], "unset") == 0)
		shell->exit = unset(shell);
	else if (ft_strcmp(shell->args[0], "exit") == 0)
		ft_exit(shell);
	return (shell->exit);
}

int built_in(t_shell *shell)
{
	if (check_builtin(shell->args) == 1)
	{	
		if (shell->redir_type != -1)
			make_redir(shell);
		run_builtin(shell);
		recover_std(shell);
		return (1);
	}
	else
		return (0);
}
