/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/31 16:33:42 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static int	args_error(void)
{
	write(2, "bash: cd: too many arguments\n", 29);
	return (1);
}

int	cd_home(t_shell *shell, int n)
{
	if (search_var_line("HOME", shell->envp) == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		return (1);
	}
	free_m(shell->struct_cmd[n]->args);
	shell->struct_cmd[n]->args = (char **)malloc(3 * sizeof(char *));
	shell->struct_cmd[n]->args[0] = ft_strdup("cd");
	shell->struct_cmd[n]->args[1] = ft_strdup(search_var_line("HOME",
				shell->envp));
	shell->struct_cmd[n]->args[2] = NULL;
	return (0);
}

int	cd_back(t_shell *shell, int n)
{
	char	*tmp;

	tmp = ft_strjoin(search_var_line("PWD", shell->envp), "/");
	shell->struct_cmd[n]->args[1] = ft_strjoin(tmp,
			shell->struct_cmd[n]->args[1]);
	free(tmp);
	return (0);
}

int	cd(t_shell *shell, int n)
{
	char	*tmp;
	int		pwd;
	int		oldpwd;
	char	buffer[100];
	char	*dir;

	if (!shell->envp)
		return (1);
	dir = ft_strdup(shell->struct_cmd[n]->args[1]);
	if (shell->struct_cmd[n]->args[1] == NULL)
		cd_home(shell, n);
	else if (shell->struct_cmd[n]->args[2] != NULL)
		return (args_error());
	else if (shell->struct_cmd[n]->args[1][0] != '/'
		&& ft_strcmp(shell->struct_cmd[n]->args[1], "..") != 0)
		cd_back(shell, n);
	change_var(shell, "OLDPWD", getcwd(buffer, 100));
	if (chdir(shell->struct_cmd[n]->args[1]) < 0)
		return (cmd_error(dir, errno, 1));
	change_var(shell, "PWD", getcwd(buffer, 100));
	return (0);
}
