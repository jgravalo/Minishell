/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/03 09:54:56 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

char	*for_equal(char *var)
{
	char	*new;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	i = 0;
	new = malloc(sizeof (char) * (ft_strlen(var) + 3));
	while (var[j])
	{
		if (flag == 0 && var[j] == '=')
		{
			new[i++] = var[j++];
			new[i++] = '\"';
			flag = 1;
		}
		else
			new[i++] = var[j++];
	}
	new[i++] = '\"';
	new[i] = '\0';
	return (new);
}

static char	*put_var(char *var)
{
	char	*new;

	if (ft_strchr(var, '=') != NULL)
	{
		new = for_equal(var);
		return (new);
	}
	return (NULL);
}

static void	print_env(char **envp, int *order)
{
	int		n;
	int		count;
	int		i;
	char	*var;

	i = 0;
	count = 0;
	n = count_arr(envp);
	while (n > 0)
	{
		while (order[i] != count)
			i++;
		if (ft_strncmp(envp[i], "_=", 2) != 0)
		{
			var = put_var(envp[i]);
			write(1, "declare -x ", 11);
			if (!var)
				write(1, envp[i], ft_strlen(envp[i]));
			else
			{
				write(1, var, ft_strlen(var));
				free(var);
			}
			write(1, "\n", 1);
		}
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
