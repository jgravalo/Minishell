/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:59:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 09:06:32 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf(1, "\n");
		return ;
	}
	else if (signal == SIGQUIT)
	{
		ft_printf(2, "Quit: 3\n");
	}
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

static void	set_exit(t_shell *sh, int status)
{
	if (WIFEXITED(status))
		sh->exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			sh->exit = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			sh->exit = 131;
	}
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
				set_exit(sh, status);
			}
			else
			{
				cmd_error("bash; ", errno, 1);
				return ;
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
