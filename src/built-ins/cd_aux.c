/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:08:34 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 09:52:51 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../libft/libft.h"

char	*cd_home(t_shell *sh, t_cmd **cmd, int i)
{
	if (search_var_line("HOME", sh->envp) == NULL)
	{
		ft_printf(2, "bash: cd: HOME not set\n");
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
		if (str[i] == '/' && str[i + 1] != '.')
			slashes++;
		i++;
	}
	i = 0;
	while (slashes > 1)
	{
		if (str[i] == '/' && str[i + 1] != '.')
			slashes--;
		i++;
	}
	return (copy_back_dir(str, i));
}

char	*cd_back(t_shell *sh, char *dir)
{
	char	*tmp;
	char	*tmp2;
	char	buf[200];

	free(dir);
	tmp = getcwd(buf, 200);
	if (tmp)
		tmp2 = ft_strjoin(tmp, "/");
	else
		tmp2 = ft_strjoin(sh->pwd, "/");
	tmp2 = get_back_dir(tmp2);
	return (tmp2);
}

char	*cd_last(t_shell *sh, char *dir)
{
	free(dir);
	if (search_var_line("OLDPWD", sh->envp) == NULL)
	{
		ft_printf(2, "bash: cd: OLDPWD not set\n");
		sh->exit = 1;
		return (NULL);
	}
	dir = ft_strdup(search_var_line("OLDPWD", sh->envp));
	sh->cd_last = 1;
	return (dir);
}
