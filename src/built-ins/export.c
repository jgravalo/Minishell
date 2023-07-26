/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:59:28 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 17:58:00 by dtome-pe         ###   ########.fr       */
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
		printf("n es %d\n", n);
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
		printf("order %d is count %d\n", i, count);
		count = 0;
		j = 0;
		i++;
	}
	print_env(shell->envp, order);
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

static int export_n(char *var, t_shell *shell)
{
	char	**new;
	int		i;

	if (parse_var(var) == 1)
	{
		write(2, "bash: export: `", 15);
		write(2, var, ft_strlen(var));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	new = (char **)malloc(sizeof(char *) * (count_arr(shell->envp) + 2));
	if (!new)
		return (1);
	i = 0;
	while (shell->envp[i] != NULL)
	{	
		new[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	i++;
	new[i] = NULL;
	free(shell->envp);
	shell->envp = new;
	return (0);
}

int	export(t_shell *shell)
{
	int	i;
	
	if (shell->args[1] == NULL)
	{	
		printf("entra en order env\n");
		order_env(shell, shell->envp);
		return (0);
	}
	i = 1;
	while (shell->args[i])
	{	
		export_n(shell->args[i], shell);
		i++;
	}
	printf("last variable is %s\n", shell->envp[count_arr(shell->envp) - 1]);
	return (0);
}