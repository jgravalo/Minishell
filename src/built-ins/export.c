/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/18 23:26:02 by theonewhokn      ###   ########.fr       */
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

static int	parse_var(char *var)
{
	int i;

	i = 0;
	if (is_digit(var[i]) == 1 || is_alpha(var[i]) == 0)
		return (1);
	i++;
	while(var[i])
	{	
		if (var[i] == '=')
			return (0);
		if (is_alpha_num(var[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	export_n(char *var, char ***envp)
{
	char	**new;
	int		i;

	if (parse_var(var) == 1)
	{
		write(2, "bash: export: `", 15);
		write(2, var, ft_strlen(var));
		write(2, "': not a valid identifier\n", 27);
	}
	new = (char **)malloc(sizeof(char *) * count_arr(*envp) + 2);
	if (!new)
		return (1);
	i = 0;
	while ((*envp)[i])
	{	
		new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new[i++] = ft_strdup(var);
	new[i] = NULL;
	*envp = new;
	return (0);
}

int	export(char **args, char ***envp)
{
	int	i;
	
	if (args[1] == NULL)
	{	
		order_env(*envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		export_n(args[i], envp);
		i++;
	}
	i = 0;
	while ((*envp)[i])
	{
		printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}
