/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:22:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/13 00:07:29 by theonewhokn      ###   ########.fr       */
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
	if (ft_strchr(envp[env], '=') == NULL)
		return (NULL);
	var = ft_strchr(envp[env], '=') + 1;
	return (var);
}

int	is_existing(char *line, char **envp)
{
	int i;
	char *var;

	i = 0;
	while (line[i] != '+' && line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_substr(line, 0, i);
	i = 0;
	while (envp[i])
	{	
		if (ft_varcmp(var, envp[i], ft_strlen(var)) == 0)
		{	
			if (ft_strchr(envp[i], '=') != NULL && ft_strchr(line, '=') == NULL)
				return (1);
			else
				return (2);
		}
		i++;
	}
	free (var);
	return (0);
}
