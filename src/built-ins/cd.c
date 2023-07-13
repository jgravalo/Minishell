/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:55:25 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 18:10:08 by theonewhokn      ###   ########.fr       */
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

	if (!envp)
		return (1);
	if (rute == NULL)
		rute = search_var("HOME", envp);
	else if (rute[0] != '/' && ft_strcmp(rute, "..") != 0)
	{
		tmp = ft_strjoin(search_var("PWD", envp), "/");
		rute = ft_strjoin(tmp, rute);
		free(tmp);
	}
	printf("%s\n", getcwd(buffer, 100));
	oldpwd = search_var_num("OLDPWD", envp);
	envp[oldpwd] = ft_strjoin("OLDPWD=", getcwd(buffer, 100));
	if (chdir(rute) < 0)
		return (cd_error(rute));
	pwd = search_var_num("PWD", envp);
	envp[pwd] = ft_strjoin("PWD=", getcwd(buffer, 100));
	printf("%s\n", getcwd(buffer, 100));
	return (0);
}
