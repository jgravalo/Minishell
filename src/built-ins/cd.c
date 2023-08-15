/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/15 14:23:34 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd_error(char *rute)
{
	write(2, "cd: no such file or directory: ", 31);
	write(2, rute, ft_strlen(rute));
	write(2, "\n", 1);
	return (1);
}

static int	args_error(void)
{
	write(2, "cd: too many arguments\n", 24);
	return (1);
}

int	cd(t_shell *shell, char **envp)
{
	char	*tmp;
	int		pwd;
	int		oldpwd;
	char	buffer[100];
	int		join;

	join = 0;
	if (!envp)
		return (1);
	if (shell->args[2] != NULL)
		return (args_error());
	if (shell->args[1] == NULL)
		shell->args[1] = search_var_line("HOME", envp);
	else if (shell->args[1][0] != '/' && ft_strcmp(shell->args[1], "..") != 0)
	{
		tmp = ft_strjoin(search_var_line("PWD", envp), "/");
		shell->args[1] = ft_strjoin(tmp, shell->args[1]);
		join = 1;
		free(tmp);
	}
	oldpwd = search_var_num("OLDPWD", envp);
	free(envp[oldpwd]);
	envp[oldpwd] = ft_strjoin("OLDPWD=", getcwd(buffer, 100));
	if (chdir(shell->args[1]) < 0)
		return (cd_error(shell->args[1]));
	pwd = search_var_num("PWD", envp);
	free(envp[pwd]);
	envp[pwd] = ft_strjoin("PWD=", getcwd(buffer, 100));
	return (0);
}
