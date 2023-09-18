/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:08:34 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 10:51:58 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	*cd_home(t_shell *sh, t_cmd **cmd, int i)
{
	if (search_var_line("HOME", sh->envp) == NULL)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		sh->exit = 1;
		return (NULL);
	}
	else
	{
		free_m(cmd[i]->args);
		return (ft_strdup(search_var_line("HOME",
					sh->envp)));
	}
}

static char	*copy_back_dir(char *str, int count)
{
	char	*dir;

	dir = malloc(sizeof (char) * count + 1);
	ft_strlcpy(dir, str, count + 1);
	return (dir);
}

static char	*get_back_dir(char *str)
{
	int		i;
	int		slashes;
	char	*ptr;

	i = 0;
	slashes = 0;
	while (str[i])
	{
		if (str[i] == '/')
			slashes++;
		i++;
	}
	i = 0;
	while (slashes > 1)
	{
		if (str[i] == '/')
			slashes--;
		i++;
	}
	return (copy_back_dir(str, i));
}

char	*cd_back(t_shell *sh, t_cmd **cmd, int i)
{
	char	*tmp;
	char	*ptr;
	char	buf[100];

	tmp = ft_strjoin(getcwd(buf, 100), "/");
	cmd[i]->args[1] = get_back_dir(tmp);
	free(tmp);
	return (cmd[i]->args[1]);
}

char	*cd_last(t_shell *sh, t_cmd **cmd, int i)
{
	char	*tmp;

	if (search_var_line("OLDPWD", sh->envp) == NULL)
	{
		write(2, "bash: cd: OLDPWD not set\n", 25);
		sh->exit = 1;
		return (NULL);
	}
	tmp = ft_strdup(search_var_line("OLDPWD", sh->envp));
	if (!tmp)
		tmp = ft_strdup(sh->old_pwd);
	sh->cd_last = 1;
	cmd[i]->args[1] = ft_strdup(tmp);
	free(tmp);
	return (cmd[i]->args[1]);
}
