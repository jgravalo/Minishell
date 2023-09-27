/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:39:29 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/26 18:24:03 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

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
		if (argsize(ptr))
		{
			cmd[i]->args = malloc(sizeof (char *) * (argsize(ptr) + 1));
			while (ptr)
			{
				cmd[i]->args[j] = ft_strdup(ptr->arg);
				j++;
				ptr = ptr->next;
			}
			cmd[i]->args[j] = NULL;
		}
		else
			cmd[i]->args = NULL;
		i++;
		j = 0;
	}
}
