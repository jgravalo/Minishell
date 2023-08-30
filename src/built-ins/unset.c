/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/30 12:13:32 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int unset_n(char *var, t_shell *shell)
{
	char	**new;
	int		n;
	int		i;
	int		j;
	
	n = search_var_num(var, shell->envp);
	if (n < 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(shell->envp));
	i = 0;
	j = 0;
	while (shell->envp[i])
	{	
		if (n == i)
		{	
			i++;
			continue ;
		}
		new[j] = ft_strdup(shell->envp[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	free_m(shell->envp);
	shell->envp = new;
	return (0);
}

int	unset(t_shell *shell, int n)
{
	int	i;

	i = 1;
	if (shell->struct_cmd[n]->args[i] == NULL)
		return (0);
	while (shell->struct_cmd[n]->args[i])
	{	
		if (ft_strchr(shell->struct_cmd[n]->args[i], '=') != NULL)
		{
			write(2, "unset: ", 7);
			write(2, shell->struct_cmd[n]->args[i], ft_strlen(shell->struct_cmd[n]->args[i]));
			write(2, ": invalid parameter name\n", 26);
			shell->exit++;
		}
		shell->exit += unset_n(shell->struct_cmd[n]->args[i], shell);
		i++;
	}
	return (shell->exit);
}
