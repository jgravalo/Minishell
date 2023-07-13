/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:19 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 18:25:29 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_cd(char **args, char **envp)
{
	if (ft_strcmp(args[0], "cd") == 0)
	{
		cd(args[1], envp);
		return (0);
	}
	else
		return (1);
}

int	run_builtin(char **args, char **envp)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
	{
		env(envp);
		return (0);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		export(args, &envp);
		return (0);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		pwd(envp);
		return (0);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		unset(args, &envp);
		return (0);
	}
	else
		return (1);
}
