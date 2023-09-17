/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/17 20:59:59 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static char	*cd_home(t_shell *sh, t_cmd **cmd, int i)
{
	if (search_var_line("HOME", sh->envp) == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		sh->exit = 1;
		return (NULL);
	}
	free_m(cmd[i]->args);
	cmd[i]->args = (char **)malloc(3 * sizeof(char *));
	cmd[i]->args[0] = ft_strdup("cd");
	cmd[i]->args[1] = ft_strdup(search_var_line("HOME",
				sh->envp));
	cmd[i]->args[2] = NULL;
	return (cmd[i]->args[1]);
}

static char	*cd_back(t_shell *sh, t_cmd **cmd, int i)
{
	char	*tmp;

	tmp = ft_strjoin(search_var_line("PWD", sh->envp), "/");
	cmd[i]->args[1] = ft_strjoin(tmp,
			cmd[i]->args[1]);
	free(tmp);
	return (cmd[i]->args[1]);
}

static char	*cd_last(t_shell *sh, t_cmd **cmd, int i)
{
	char	*tmp;

	if (search_var_line("OLDPWD", sh->envp) == NULL && sh->old_pwd == NULL)
	{
		write(2, "bash: cd: OLDPWD not set\n", 25);
		sh->exit = 1;
		return (NULL);
	}
	tmp = ft_strdup(search_var_line("OLDPWD", sh->envp));
	if (!tmp)
		tmp = ft_strdup(sh->old_pwd);
	printf("%s\n", tmp);
	cmd[i]->args[1] = ft_strdup(tmp);
	free(tmp);
	return (cmd[i]->args[1]);
}

static char	*get_dir(t_shell *sh, t_cmd **cmd, int i)
{
	char	*dir;

	dir = ft_strdup(cmd[i]->args[1]);
	if (dir == NULL)
		dir = cd_home(sh, cmd, i);
	else if (ft_strlen(dir) == 0)
		return (NULL);
	else if (dir[0] != '/' && ft_strcmp(dir, "..") == 0)
		dir = cd_back(sh, cmd, i);
	else if (ft_strcmp(dir, "-") == 0)
		dir = cd_last(sh, cmd, i);
	else if (ft_strcmp(dir, ".") == 0)
		dir = search_var_line("PWD", sh->envp);
	if (!dir)
		return (NULL);
	return (dir);
}

int	cd(t_shell *sh, t_cmd **cmd, int i)
{
	char	buffer[100];
	int		chdir_return;
	char	*dir;

	if (cmd[i]->args[2] != NULL)
		return (args_error());
	dir = get_dir(sh, cmd, i);
	sh->tmp = ft_strdup(getcwd(buffer, 100));
	if (!sh->tmp)
		access_dir();
	if (chdir(dir) < 0)
		return (dir_error(dir, errno, 1));
	change_var(sh, "PWD", getcwd(buffer, 100));
	change_var(sh, "OLDPWD", sh->tmp);
	free(sh->old_pwd);
	sh->old_pwd = ft_strdup(sh->tmp);
	free(sh->tmp);
	return (0);
}
