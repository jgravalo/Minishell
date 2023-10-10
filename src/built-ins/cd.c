/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 09:31:13 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

static void	update_aux(t_shell *sh)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	ft_export(sh, "PWD");
	tmp = getcwd(buffer, 200);
	change_var(sh, "PWD", tmp);
	free(tmp);
	if (sh->pwd)
		free(sh->pwd);
	sh->pwd = getcwd(buffer, 200);
}

static void	update_pwd(t_shell *sh, int error, char *dir)
{
	char	*tmp;

	tmp = ft_strdup(search_var_line("PWD", sh->envp));
	if (!error)
	{
		if (search_var_line("OLDPWD", sh->envp)
			&& search_var_line("PWD", sh->envp) == NULL)
			ft_unset(sh, "OLDPWD");
		if (search_var_line("OLDPWD", sh->envp) == NULL
			&& search_var_line("PWD", sh->envp))
			ft_export(sh, "OLDPWD");
		change_var(sh, "OLDPWD", tmp);
		update_aux(sh);
	}
	else
	{
		change_var(sh, "OLDPWD", tmp);
		change_var(sh, "PWD", dir);
		if (sh->pwd)
			free(sh->pwd);
		sh->pwd = ft_strdup(dir);
	}
	free(tmp);
}

static void	*get_dir_aux(char *dir, t_shell *sh)
{
	char	*tmp;

	access_dir();
	free(dir);
	tmp = ft_strdup(sh->pwd);
	dir = ft_strjoin(tmp, "/.");
	update_pwd(sh, 1, dir);
	free(tmp);
	free(dir);
	return (NULL);
}

static char	*get_dir(t_shell *sh, t_cmd **cmd, int i)
{
	char	*dir;
	char	buffer[200];

	dir = ft_strdup(cmd[i]->args[1]);
	if (dir == NULL)
		dir = cd_home(sh, cmd, i);
	else if (ft_strlen(dir) == 0)
		return (NULL);
	else if (dir[0] != '/' && ft_strcmp(dir, "..") == 0)
		dir = cd_back(sh, dir);
	else if (ft_strcmp(dir, "-") == 0)
		dir = cd_last(sh, dir);
	else if (ft_strcmp(dir, ".") == 0)
	{
		free(dir);
		dir = ft_strdup(getcwd(buffer, 200));
		if (!dir)
			return (get_dir_aux(dir, sh));
	}
	return (dir);
}

int	cd(t_shell *sh, t_cmd **cmd, int i)
{
	char	*dir;

	sh->cd_last = 0;
	dir = get_dir(sh, cmd, i);
	if (!dir)
		return (sh->exit);
	if (chdir(dir) < 0)
		return (dir_error(dir, errno, 1));
	if (sh->cd_last)
		ft_printf(1, "%s\n", dir);
	update_pwd(sh, 0, NULL);
	free(dir);
	dir = NULL;
	return (0);
}
