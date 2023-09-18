/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:23:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 08:53:24 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/builtins.h"

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

int	builtin(t_shell *sh, t_cmd **cmd, int i)
{
	if (check_builtin(cmd[i]->args))
	{
		if (ft_strcmp(cmd[i]->args[0], "cd") == 0)
			sh->exit = cd(sh, cmd, i);
		else if (ft_strcmp(cmd[i]->args[0], "echo") == 0)
			sh->exit = echo(cmd[i]->args);
		else if (ft_strcmp(cmd[i]->args[0], "env") == 0)
			sh->exit = env(sh->envp);
		else if (ft_strcmp(cmd[i]->args[0], "export") == 0)
			sh->exit = export(sh, cmd, i);
		else if (ft_strcmp(cmd[i]->args[0], "pwd") == 0)
			sh->exit = pwd(sh->envp);
		else if (ft_strcmp(cmd[i]->args[0], "unset") == 0)
			sh->exit = unset(sh, cmd, i);
		else if (ft_strcmp(cmd[i]->args[0], "exit") == 0)
			ft_exit(sh, cmd, i);
		return (1);
	}
	else
		return (0);
}
