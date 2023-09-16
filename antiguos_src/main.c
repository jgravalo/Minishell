/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:11:14 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 14:07:13 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_ins(char **argv, char **envp)
{
	int	out;

	out = 0;
	if (ft_strcmp(argv[1], "cd") == 0)
	{
		out = cd(argv[2], envp);
		env(envp);
	}
	else if (ft_strcmp(argv[1], "echo") == 0)
		out = echo(++argv);
	else if (ft_strcmp(argv[1], "env") == 0)
		out = env(envp);
	else if (ft_strcmp(argv[1], "pwd") == 0)
		out = pwd(envp);
	else if (ft_strcmp(argv[1], "unset") == 0)
	{
		unset(++argv, &envp);
	}
	else if (ft_strcmp(argv[1], "export") == 0)
		out = export(++argv, &envp);
	else if (ft_strcmp(argv[1], "exit") == 0)
		exit(0);
	return (out);
}

/* int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	return (built_ins(argv, envp));
}  */