/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:59:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:25:11 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		return ;
	}
	else if (signal == SIGQUIT)
		kill(0, SIGQUIT);
}

static void	set_waitsig(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	ft_memset(&sigint, 0, sizeof(struct sigaction));
	ft_memset(&sigquit, 0, sizeof(struct sigaction));
	sigint.sa_flags = SA_RESTART;
	sigquit.sa_flags = SA_RESTART;
	sigint.sa_handler = handler;
	sigquit.sa_handler = handler;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	parent_wait(t_shell *sh, t_cmd **cmd)
{
	int		status;
	int		i;
	pid_t	pid;

	status = 0;
	while (sh->children != 0)
	{
		i = 0;
		while (i < sh->pipes + 1)
		{
			set_waitsig();
			pid = waitpid(cmd[i]->pid, &status, 0);
			if (pid > 0)
			{
				sh->children--;
				if (WIFEXITED(status))
					sh->exit = WEXITSTATUS(status);
			}
			i++;
		}
	}
}

void	parent_close(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->pipes)
	{
		close(sh->p[i].p[READ]);
		close(sh->p[i].p[WRITE]);
		i++;
	}
}
