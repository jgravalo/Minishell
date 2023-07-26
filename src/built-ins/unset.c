/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 19:19:25 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int unset_n(char *var, t_shell *shell)
{
	char	**new;
	int		n;
	int		i;
	
	n = search_var_num(var, shell->envp);
	if (n < 0)
		return (1);
	new = (char **)malloc(sizeof(char *) * count_arr(shell->envp));
	i = 0;
	while (shell->envp[i])
	{	
		if (n == i)
		{	
			i++;
			continue ;
		}
		new[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new[i] = NULL;
	free_m(shell->envp);
	shell->envp = new;
	return (0);
}

int	unset(t_shell *shell)
{
	int	i;
	int exit;

	i = 1;
	exit = 0;
	if (shell->args[i] == NULL)
		return (1);
	while (shell->args[i])
	{	
		if (ft_strchr(shell->args[i], '=') != NULL)
		{
			exit++;
			write(2, "unset: ", 7);
			write(2, shell->args[i], ft_strlen(shell->args[i]));
			write(2, ": invalid parameter name\n", 26);
			break ;
		}
		exit = unset_n(shell->args[i], shell);
		i++;
	}
	return (exit);
}
