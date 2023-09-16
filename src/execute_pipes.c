/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:20:53 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 07:52:00 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	mid_cmd(t_shell *sh, int i)
{
	int	store;

	store = i;
	i++;
	while (i < sh->pipes)
	{
		close(sh->p[i].p[READ]);
		close(sh->p[i].p[WRITE]);
		i++;
	}
	i = store;
	i -= 2;
	while (i >= 0)
	{
		close(sh->p[i].p[READ]);
		close(sh->p[i].p[WRITE]);
		i--;
	}
}

static void	close_pipes(t_shell *sh, int i)
{
	if (i == 0)
	{
		i++;
		while (i < sh->pipes)
		{
			close(sh->p[i].p[READ]);
			close(sh->p[i].p[WRITE]);
			i++;
		}
	}
	else if (i == sh->pipes)
	{
		i -= 2;
		while (i >= 0)
		{
			close(sh->p[i].p[READ]);
			close(sh->p[i].p[WRITE]);
			i--;
		}
	}
	else
		mid_cmd(sh, i);
}

static void	check_pipe(t_shell *sh, t_cmd **cmd, int i)
{
	if (i == 0)
	{
		cmd[i]->in_pipe = 0;
		cmd[i]->out_pipe = 1;
	}
	else if (i == sh->pipes)
	{
		cmd[i]->in_pipe = 1;
		cmd[i]->out_pipe = 0;
	}
	else 
	{
		cmd[i]->in_pipe = 1;
		cmd[i]->out_pipe = 1;
	}
}

static void	handle_pipes(t_shell *sh, t_cmd **cmd, int i)
{
	if (cmd[i]->in_pipe == 1)
	{	
		printf("tocamos in pipe\n");
		close(sh->p[i - 1].p[WRITE]);
		dup2(sh->p[i - 1].p[READ], STDIN_FILENO);
		close(sh->p[i - 1].p[READ]);
	}
	if (cmd[i]->out_pipe == 1)
	{
		close(sh->p[i].p[READ]);
		dup2(sh->p[i].p[WRITE], STDOUT_FILENO);
		close(sh->p[i].p[WRITE]);
	}
}

void	execute_pipes(t_shell *sh, t_cmd **cmd, int i)
{
	if (sh->pipes)
	{
		check_pipe(sh, cmd, i);
		handle_pipes(sh, cmd, i);
		if (sh->pipes > 1)
			close_pipes(sh, i);
	}
}
