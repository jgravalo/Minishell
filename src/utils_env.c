/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:22:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/24 11:28:55 by theonewhokn      ###   ########.fr       */
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
		if (!name[j] && envp[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*search_var(char *name, char **envp)
{
	int		env;
	char	*var;

	env = search_var_num(name, envp);
	if (env < 0)
		return (NULL);
	var = ft_strchr(envp[env], '=') + 1;
	return (var);
}
