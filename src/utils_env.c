/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:22:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 18:50:31 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_var_num(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (name[j] && envp[i][j] == name[j])
			j++;
		if (!name[j] && envp[i][j] == '=' || envp[i][j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*search_var_line(char *name, char **envp)
{
	int		env;
	char	*var;

	env = search_var_num(name, envp);
	if (env < 0)
		return (NULL);
	var = ft_strchr(envp[env], '=') + 1;
	return (var);
}

int	is_existing(char *line, char **envp)
{
	int i;
	char *var;

	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_substr(line, 0, i);
	while (envp[i])
	{
		if (ft_varcmp(var, envp[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	free (var);
	return (0);
}
