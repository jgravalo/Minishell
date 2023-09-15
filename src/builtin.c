/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:23:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:24:50 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	builtin(t_shell *shell, t_cmd **cmd, int *i)
{
	if (check_builtin(cmd[*i]->args))
	{
		if (ft_strcmp(cmd[*i]->args[0], "cd") == 0)
			shell->exit = cd(shell, cmd, i);
		else if (ft_strcmp(cmd[*i]->args[0], "echo") == 0)
			shell->exit = echo(cmd[*i]->args);
		else if (ft_strcmp(cmd[*i]->args[0], "env") == 0)
			shell->exit = env(shell->envp);
		else if (ft_strcmp(cmd[*i]->args[0], "export") == 0)
			shell->exit = export(shell, cmd, i);
		else if (ft_strcmp(cmd[*i]->args[0], "pwd") == 0)
			shell->exit = pwd(shell->envp);
		else if (ft_strcmp(cmd[*i]->args[0], "unset") == 0)
			shell->exit = unset(shell, cmd, i);
		else if (ft_strcmp(cmd[*i]->args[0], "exit") == 0)
			ft_exit(shell, cmd, i);
		return (1);
	}
	else
		return (0);
}
