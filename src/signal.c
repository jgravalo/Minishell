/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:24:57 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/23 10:53:21 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../inc/minishell.h"

pid_t *g_pid;

void	handler(int signal)
{	
	int i;

	i = 0;
	if (signal == SIGINT)
	{	
		kill(g_pid[i], SIGINT);
		i++;
	}
	write(1, "\n", 1);
}

static int	wait_for_children(t_shell *shell)
{	
	pid_t	pid;
	
	while (shell->children)
	{	
		pid = waitpid(-1, &shell->exit, WNOHANG);
		if (pid > 0)
			shell->children--;
	}
	return (shell->exit);
}

int	set_signals(t_shell *shell, char **envp)
{
	sigset_t			sigset;
	struct sigaction	sa;
	int					status;

	g_pid = shell->pid;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaddset(&sigset, SIGINT);
	return (wait_for_children(shell));
}
