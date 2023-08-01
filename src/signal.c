/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:24:57 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/01 17:56:18 by dtome-pe         ###   ########.fr       */
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
		while (g_pid[i])
		{
			kill(g_pid[i], SIGINT);
			i++;
		}
		write(1, "\n", 1);
	}
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
