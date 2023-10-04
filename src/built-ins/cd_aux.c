/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:08:34 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:08:26 by dtome-pe         ###   ########.fr       */
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
		free(cmd[i]->args[1]);
		return (ft_strdup(search_var_line("HOME",
					sh->envp)));
	}
}

static char	*copy_back_dir(char *str, int count)
{
	char	*dir;

	dir = malloc(sizeof (char) * count + 1);
	check_malloc_error(dir);
	ft_strlcpy(dir, str, count + 1);
	free(str);
	return (dir);
}

static char	*get_back_dir(char *str)
{
	int		i;
	int		slashes;

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

char	*cd_back(char *dir)
{
	char	*tmp;
	char	buf[100];

	free(dir);
	tmp = ft_strjoin(getcwd(buf, 200), "/");
	tmp = get_back_dir(tmp);
	return (tmp);
}

char	*cd_last(t_shell *sh, char *dir)
{
	char	*tmp;

	free(dir);
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
	return (tmp);
}
