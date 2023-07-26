/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 17:14:04 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_builtin(char **args, char **envp)
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
	//printf("args 0 es %s\n", args[0]);
	if (ft_strcmp(shell->args[0], "cd") == 0)
		return (cd(shell->args[1], shell->envp));
	else if (ft_strcmp(shell->args[0], "echo") == 0)
		return (echo(shell->args));
	else if (ft_strcmp(shell->args[0], "env") == 0)
		return (env(shell->envp));
	else if (ft_strcmp(shell->args[0], "export") == 0)
	{	
		export(shell);
		printf("count arr is %d\n", count_arr(shell->envp));
		return (0);
	}
	else if (ft_strcmp(shell->args[0], "pwd") == 0)
		return (pwd(shell->envp));
	else if (ft_strcmp(shell->args[0], "unset") == 0)
		return (unset(shell->args, shell->envp));
	else if (ft_strcmp(shell->args[0], "exit") == 0)
		exit(1);
	else
		return (1);
}
