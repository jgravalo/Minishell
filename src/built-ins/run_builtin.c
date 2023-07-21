/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/21 14:35:12 by theonewhokn      ###   ########.fr       */
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

int	run_builtin(char **args, char **envp)
{	
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd(args[1], envp));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env(envp));
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(args, &envp));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, &envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(1);
	else
		return (1);
}
