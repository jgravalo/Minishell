/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/31 12:34:06 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	args_error(void)
{
	write(2, "bash: cd: too many arguments\n", 29);
	return (1);
}

int	cd(t_shell *shell, int n)
{
	char	*tmp;
	int		pwd;
	int		oldpwd;
	char	buffer[100];
	int		join;
	char 	*dir;

	join = 0;
	if (!shell->envp)
		return (1);
	dir = ft_strdup(shell->struct_cmd[n]->args[1]);
	if (shell->struct_cmd[n]->args[1] == NULL)
	{
		if (search_var_line("HOME", shell->envp) == NULL)
		{
			write(2, "bash: cd: HOME not set\n", 23);
			return (1);
		}
		free_m(shell->struct_cmd[n]->args);
		shell->struct_cmd[n]->args = (char **)malloc(3 * sizeof(char *));
		shell->struct_cmd[n]->args[0] = ft_strdup("cd");
		shell->struct_cmd[n]->args[1] = ft_strdup(search_var_line("HOME", shell->envp));
		shell->struct_cmd[n]->args[2] = NULL;
	}
	else if (shell->struct_cmd[n]->args[2] != NULL)
		return (args_error());
	else if (shell->struct_cmd[n]->args[1][0] != '/' && ft_strcmp(shell->struct_cmd[n]->args[1], "..") != 0)
	{
		tmp = ft_strjoin(search_var_line("PWD", shell->envp), "/");
		shell->struct_cmd[n]->args[1] = ft_strjoin(tmp, shell->struct_cmd[n]->args[1]);
		join = 1;
		free(tmp);
	}
	change_var(shell, "OLDPWD", getcwd(buffer, 100));
	if (chdir(shell->struct_cmd[n]->args[1]) < 0)
		return (cmd_error(dir, errno, 1));
	change_var(shell, "PWD", getcwd(buffer, 100));
	return (0);
}
