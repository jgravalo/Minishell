/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/03 10:05:22 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

static void	print_env(char **envp, int *order)
{
	int		n;
	int		count;
	int		i;
	char	*var;

	i = 0;
	count = 0;
	n = count_arr(envp);
	var = NULL;
	while (n > 0)
	{
		while (order[i] != count)
			i++;
		if (ft_strncmp(envp[i], "_=", 2) != 0)
			write_var(var, envp, i);
		i = 0;
		count++;
		n--;
	}
}

static void	order_env(t_shell *shell, char **envp)
{
	int	*order;
	int	i;
	int	count;
	int	j;

	i = 0;
	order = (int *)malloc(sizeof (int) * count_arr(shell->envp));
	while (shell->envp[i])
	{
		j = 0;
		count = 0;
		while (shell->envp[j] != NULL)
		{
			if (ft_strcmp(shell->envp[i], envp[j]) > 0)
				count++;
			j++;
		}
		order[i] = count;
		i++;
	}
	print_env(shell->envp, order);
	free(order);
}

int	export(t_shell *shell, t_cmd **cmd, int i)
{
	int	j;

	if (cmd[i]->args[1] == NULL)
	{
		order_env(shell, shell->envp);
		return (0);
	}
	j = 1;
	while (cmd[i]->args[j])
	{
		shell->exit = export_n(cmd[i]->args[j], shell);
		j++;
	}
	return (shell->exit);
}
