/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 13:57:02 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd_error(char *rute)
{
	write(1, "cd: no such file or directory: ", 31);
	write(1, rute, ft_strlen(rute));
	write(1, "\n", 1);
	return (1);
}

int	cd(char *rute, char **envp)
{
	char	*tmp;
	int		pwd;
	int		oldpwd;
	char	buffer[100];
	int		join;

	join = 0;
	if (!envp)
		return (1);
	if (rute == NULL)
		rute = search_var("HOME", envp);
	else if (rute[0] != '/' && ft_strcmp(rute, "..") != 0)
	{
		tmp = ft_strjoin(search_var("PWD", envp), "/");
		rute = ft_strjoin(tmp, rute);
		join = 1;
		free(tmp);
	}
	oldpwd = search_var_num("OLDPWD", envp);
	free(envp[oldpwd]);
	envp[oldpwd] = ft_strjoin("OLDPWD=", getcwd(buffer, 100));
	if (chdir(rute) < 0)
		return (cd_error(rute));
	pwd = search_var_num("PWD", envp);
	free(envp[pwd]);
	envp[pwd] = ft_strjoin("PWD=", getcwd(buffer, 100));
	if (join == 1)
		free(rute);
	return (0);
}
