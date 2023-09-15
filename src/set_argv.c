/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:39:29 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 14:18:15 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_argv(t_cmd **cmd)
{
	int		i;
	int		j;
	t_arg	*ptr;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		ptr = cmd[i]->arg_x;
		cmd[i]->args = malloc(sizeof (char *) * (argsize(ptr) + 1));
		while (ptr)
		{
			cmd[i]->args[j] = ft_strdup(ptr->arg);
			j++;
			ptr = ptr->next;
		}
		cmd[i]->args[j] = NULL;
		i++;
		j = 0;
	}
}
