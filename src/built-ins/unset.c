/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 15:45:29 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**unset_n(char *var, char **envp)
{
	char	**new;
	int		n;
	int		i;

	n = search_var_num(var, envp);
	if (n < 0)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * count_arr(envp));
	i = 0;
	while (envp[i])
	{	
		if (n == i)
		{	
			i++;
			break ;
		}
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new [i] = NULL;
	free_m(envp);
	return (new);
}

int	unset(char **argv, char **envp)
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
		envp = unset_n(argv[i], envp);
		i++;
	}
	return (exit);
}
