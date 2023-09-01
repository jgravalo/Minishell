/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/01 11:14:10 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	args_error(void)
{
	write(2, "bash: cd: too many arguments\n", 29);
	return (1);
}

char	*cd_home(t_shell *shell, int n)
{	
	if (search_var_line("HOME", shell->envp) == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		shell->exit = 1;
		return (NULL);
	}
	free_m(shell->struct_cmd[n]->args);
	shell->struct_cmd[n]->args = (char **)malloc(3 * sizeof(char *));
	shell->struct_cmd[n]->args[0] = ft_strdup("cd");
	shell->struct_cmd[n]->args[1] = ft_strdup(search_var_line("HOME",
				shell->envp));
	shell->struct_cmd[n]->args[2] = NULL;
	return (shell->struct_cmd[n]->args[1]);
}

char *cd_back(t_shell *shell, int n)
{
	char	*tmp;

	tmp = ft_strjoin(search_var_line("PWD", shell->envp), "/");
	shell->struct_cmd[n]->args[1] = ft_strjoin(tmp,
			shell->struct_cmd[n]->args[1]);
	free(tmp);
	return (shell->struct_cmd[n]->args[1]);
}

char	*cd_last(t_shell *shell, int n)
{
	char	*tmp;

	if (search_var_line("OLDPWD", shell->envp) == NULL && shell->old_pwd == NULL)
	{
		write(2, "bash: cd: OLDPWD not set\n", 25);
		shell->exit = 1;
		return (NULL);
	}
	tmp = ft_strjoin(search_var_line("OLDPWD", shell->envp), "/");
	if (ft_strcmp(tmp, "/") == 0) // si no hay variable OLDPWD, copia el oldpwd interno de la shell
		tmp = ft_strdup(shell->old_pwd);
	printf("%s\n", tmp); // se imprime directorio como en bash
	shell->struct_cmd[n]->args[1] = ft_strdup(tmp);
	free(tmp);
	return (shell->struct_cmd[n]->args[1]);
}

int	cd(t_shell *shell, int n)
{
	char	*tmp;
	char	buffer[100];
	char	*dir;

	if (!shell->envp)
		return (1);
	dir = ft_strdup(shell->struct_cmd[n]->args[1]);
	if (dir == NULL)
		dir = cd_home(shell, n);
	else if (shell->struct_cmd[n]->args[2] != NULL)
		return (args_error());
	else if (dir[0] != '/' && ft_strcmp(dir, "..") == 0)
		dir = cd_back(shell, n);
	else if (ft_strcmp(dir, "-") == 0) // implementamos cd -, ir a OLDPWD
		dir = cd_last(shell, n);
	if (!dir)
			return (1);
	tmp = ft_strdup(getcwd(buffer, 100));
	if (chdir(dir) < 0)
		return (cmd_error(dir, errno, 1));
	change_var(shell, "PWD", getcwd(buffer, 100)); // solo actualizamos oldpwd si el cambio de directorios es correcto
	change_var(shell, "OLDPWD", tmp);
	shell->old_pwd = ft_strdup(tmp);
	return (0);
}
