/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:11:53 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/09 13:49:48 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			argclear(&cmd[i]->arg);
			argclear(&cmd[i]->arg_x);
			redclear(&cmd[i]->red);
			redclear(&cmd[i]->red_x);
			free_m(cmd[i]->args);
			free(cmd[i]->path);
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}

void	free_sh(t_shell *sh)
{
	tokclear(&sh->tok);
	free(sh->readline);
	free_cmd(sh->s_cmd);
	free(sh->pwd);
	sh->pwd = NULL;
}
