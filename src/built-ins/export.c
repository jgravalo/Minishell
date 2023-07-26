/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 18:20:12 by dtome-pe         ###   ########.fr       */
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
	while (n > 0)
	{	
		while (order[i] != count)
			i++;
		write(1, "declare -x ", 12);
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i = 0;
		count++;
		n--;
	}
}

static void	order_env(t_shell *shell, char **envp)
{
	int *order;
	int i;
	int count;
	int j;

	count = 0;
	i = 0;
	j = 0;
	order = (int *)malloc(sizeof (int) * count_arr(shell->envp));
	while (shell->envp[i])
	{	
		while (shell->envp[j] != NULL)
		{	
			if (ft_strcmp(shell->envp[i], envp[j]) > 0)
				count++;
			j++;
		}
		order[i] = count;
		count = 0;
		j = 0;
		i++;
	}
	print_env(shell->envp, order);
	free(order);
}

int	export(t_shell *shell)
{
	int	i;
	
	if (shell->args[1] == NULL)
	{	
		order_env(shell, shell->envp);
		return (0);
	}
	i = 1;
	while (shell->args[i])
	{	
		export_n(shell->args[i], shell);
		i++;
	}
	return (0);
}