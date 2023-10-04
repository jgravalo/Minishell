/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:39:29 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:44:06 by dtome-pe         ###   ########.fr       */
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
			check_malloc_error(cmd[i]->args);
			while (ptr)
			{
				cmd[i]->args[j++] = ft_strdup(ptr->arg);
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
