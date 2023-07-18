/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/18 22:34:14 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void print_env(char **envp, int *order)
{
	int n;
	int count;
	int i;

	i = 0;
	count = 0;
	n = count_arr(envp);
	while (n)
	{
		while (order[i])
		{	
			if (order[i] == count)
			{
				write(1, "declare -x ", 12);
				write(1, envp[i], ft_strlen(envp[i]));
				write(1, "\n", 1);
				break;
			}
			i++;
		}
		i = 0;
		count++;
		n--;
	}
}

static void	order_env(char **envp)
{
	int *order;
	int i;
	int count;
	int j;

	i = 0;
	j = 0;
	order = (int *)malloc(sizeof (int) * count_arr(envp));
	while (envp[i])
	{	
		while (envp[j + 1])
		{
			if (ft_strcmp(envp[i], envp[j + 1]) > 0)
				count++;
			j++;
		}
		order[i] = count;
		count = 0;
		j = 0;
		i++;
	}
	print_env(envp, order);
	free(order);
}

int	export_n(char *var, char ***envp)
{
	char	**new;
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	if (var[i] != '=')
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(*envp) + 2);
	i = 1;
	while (*envp[i])
	{
		new[i] = *envp[i];
		i++;
	}
	new[i] = var;
	*envp = new;
	return (0);
}

int	export(char **args, char ***envp)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{	
		order_env(*envp);
		return (0);
	}
	while (args[i])
	{
		export_n(args[i], envp);
		i++;
	}
	return (0);
}
