/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:11:53 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 12:33:25 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("entramos cmd %d\n", i);
		argclear(&cmd[i]->arg);
		argclear(&cmd[i]->arg_x);
		redclear(&cmd[i]->red);
		redclear(&cmd[i]->red_x);
		free_m(cmd[i]->args);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_sh(t_shell *sh)
{
	tokclear(&sh->tok);
	free(sh->readline);
	free_cmd(sh->s_cmd);
}
