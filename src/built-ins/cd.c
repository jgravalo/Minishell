/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 16:00:33 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"

static void	update_pwd(t_shell *sh, int error, char *dir)
{
	char	buffer[100];

	if (!error)
	{
		if (search_var_line("OLDPWD", sh->envp) 
			&& search_var_line("PWD", sh->envp) == NULL)
			ft_unset(sh, "OLDPWD");
		if (search_var_line("OLDPWD", sh->envp) == NULL 
			&& search_var_line("PWD", sh->envp))
			ft_export(sh, "OLDPWD");
		change_var(sh, "OLDPWD", ft_strdup(search_var_line("PWD", sh->envp)));
		change_var(sh, "PWD", getcwd(buffer, 100));
		sh->pwd = ft_strdup(getcwd(buffer, 100));
		sh->old_pwd = ft_strdup(search_var_line("PWD", sh->envp));
	}
	else
	{
		change_var(sh, "OLDPWD", ft_strdup(search_var_line("PWD", sh->envp)));
		change_var(sh, "PWD", dir);
		sh->pwd = ft_strdup(dir);
	}
}

static char	*get_dir(t_shell *sh, t_cmd **cmd, int i)
{
	char	*dir;
	char	buffer[100];

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
	{
		dir = ft_strdup(getcwd(buffer, 100));
		if (!dir)
		{
			access_dir();
			dir = ft_strdup(sh->pwd);
			dir = ft_strjoin(dir, "/.");
			update_pwd(sh, 1, dir);
			return (NULL);
		}
	}
	return (dir);
}

int	cd(t_shell *sh, t_cmd **cmd, int i)
{
	char	buffer[100];
	int		chdir_return;
	char	*dir;

	sh->cd_last = 0;
	if (count_arr(cmd[i]->args) > 2)
		return (args_error());
	dir = get_dir(sh, cmd, i);
	if (!dir)
		return (sh->exit);
	if (chdir(dir) < 0)
		return (dir_error(dir, errno, 1));
	if (sh->cd_last)
		printf("%s\n", dir);
	update_pwd(sh, 0, NULL);
	return (0);
}
