/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/25 07:58:41 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	unset_n(char *var, char ***envp)
{
	char	**new;
	int		n;
	int		i;

	n = search_var_num(var, *envp);
	if (n < 0)
		return (1);
	new = (char **)malloc(sizeof(char *) * count_arr(*envp));
	i = 0;
	while ((*envp)[i])
	{	
		if (n == i)
		{	
			i++;
			break ;
		}
		new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new [i] = NULL;
	*envp = new;
	return (0);
}

int	unset(char **argv, char ***envp)
{
	int	i;
	int exit;

	i = 1;
	exit = 0;
	if (argv[i] == NULL)
		return (1);
	while (argv[i])
	{	
		if (ft_strchr(argv[i], '=') != NULL)
		{
			exit++;
			break;
		}
		exit += unset_n(argv[i], envp);
		i++;
	}
	return (exit);
}
