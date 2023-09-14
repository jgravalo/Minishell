/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/14 15:45:58 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	args_error(void)
{
	write(2, "bash: cd: too many arguments\n", 29);
	return (1);
}

char	*cd_home(t_shell *shell, t_cmd **cmd, int i)
{	
	if (search_var_line("HOME", shell->envp) == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		shell->exit = 1;
		return (NULL);
	}
	free_m(cmd[i]->args);
	cmd[i]->args = (char **)malloc(3 * sizeof(char *));
	cmd[i]->args[0] = ft_strdup("cd");
	cmd[i]->args[1] = ft_strdup(search_var_line("HOME",
				shell->envp));
	cmd[i]->args[2] = NULL;
	return (cmd[i]->args[1]);
}

char *cd_back(t_shell *shell, t_cmd **cmd, int i)
{
	char	*tmp;

	tmp = ft_strjoin(search_var_line("PWD", shell->envp), "/");
	cmd[i]->args[1] = ft_strjoin(tmp,
			cmd[i]->args[1]);
	free(tmp);
	return (cmd[i]->args[1]);
}

char	*cd_last(t_shell *shell, t_cmd **cmd, int i)
{
	char	*tmp;

	if (search_var_line("OLDPWD", shell->envp) == NULL && shell->old_pwd == NULL)
	{
		write(2, "bash: cd: OLDPWD not set\n", 25);
		shell->exit = 1;
		return (NULL);
	}
	tmp = ft_strdup(search_var_line("OLDPWD", shell->envp));
	if (!tmp) // si no hay variable OLDPWD, copia el oldpwd interno de la shell
		tmp = ft_strdup(shell->old_pwd);
	printf("%s\n", tmp); // se imprime directorio como en bash
	cmd[i]->args[1] = ft_strdup(tmp);
	free(tmp);
	return (cmd[i]->args[1]);
}

int	cd(t_shell *shell, t_cmd **cmd, int i)
{
	char	*tmp;
	char	buffer[100];
	char	*dir;

	if (cmd[i]->args[2] != NULL)
		return (args_error());
	if (!shell->envp)
		return (1);
	dir = ft_strdup(cmd[i]->args[1]);
	if (dir == NULL)
		dir = cd_home(shell, cmd, i);
	else if (ft_strlen(dir) == 0)
		return (0);
	else if (dir[0] != '/' && ft_strcmp(dir, "..") == 0)
		dir = cd_back(shell, cmd, i);
	else if (ft_strcmp(dir, "-") == 0) // implementamos cd -, ir a OLDPWD
		dir = cd_last(shell, cmd, i);
	if (!dir)
			return (1);
	tmp = ft_strdup(getcwd(buffer, 100));
	if (chdir(dir) < 0)
		return (dir_error(dir, errno, 1));
	change_var(shell, "PWD", getcwd(buffer, 100)); // solo actualizamos oldpwd si el cambio de directorios es correcto
	change_var(shell, "OLDPWD", tmp);
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(tmp);
	free(tmp);
	return (0);
}
