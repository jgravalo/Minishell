/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:22:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 16:43:06 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	move_ptrs(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

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
	int		i;
	char	*var;

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

int	ft_varcmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (s2[i] == '+' || s2[i] == '=' || s2[i] == '\0')
		return (0);
	else
		return (-1);
}
