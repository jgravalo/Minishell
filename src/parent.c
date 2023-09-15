/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:59:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 22:07:58 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (signal == SIGQUIT)
		kill(0, SIGQUIT);
}

/* void	set_signals(t_shell *sh, char **envp)
{
	sigset_t			sigset;
	struct sigaction	sa;
	int					status;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaddset(&sigset, SIGINT);
	sigaction(SIGQUIT, &sa, NULL);
	sigaddset(&sigset, SIGQUIT);
} */

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
