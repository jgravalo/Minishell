/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/01 20:02:07 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_builtin(char **args)
{	
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
		shell->exit = cd(shell->args[1], shell->envp);
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
