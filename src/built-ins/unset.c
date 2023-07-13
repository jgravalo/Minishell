/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 18:07:05 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unset_aux(char ***envp, char **new, int n)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (*envp[i + j])
	{
		if (i == n)
		{
			free(*envp[i]);
			j++;
		}
		new[i] = *envp[i + j];
		i++;
	}
}

int	unset_n(char *var, char ***envp)
{
	char	**new;
	int		i;
	int		j;
	int		n;

	n = search_var_num(var, *envp);
	if (n < 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(*envp));
	i = 1;
	j = 0;
	env(*envp);
	unset_aux(envp, new, n);
	env(*envp);
	*envp = new;
	return (0);
}

int	unset(char **argv, char ***envp)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_n(argv[i], envp);
		i++;
	}
	return (0);
}
