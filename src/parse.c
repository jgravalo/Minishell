/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/01 10:53:09 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	parse_line(t_shell *shell, int i)
{	
	char	*tmp;

	check_pipe(shell, i);
	shell->pid[i] = fork();
	if (shell->pid[i] > 0)
		parent_routine(shell, i);
	if (shell->pid[i] == 0)
		child_routine(shell, i);
	parent_close(shell);
	shell->pid[i] = 0;
	return (set_signals(shell, shell->envp));
}

static void init_shell(t_shell *shell)
{	
	shell->pipex = count_ascii(shell->readline, '|');
	if (shell->pipex > 0)
		shell->pipes = ft_split(shell->readline, '|');
	if (shell->pipex == 0)
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (2));
	else
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (shell->pipex + 1));
	shell->children = 0;
	shell->last_builtin = 0;
	shell->infd	= -1;
	shell->outfd = -1;
	shell->redir_type = -1;
}

void parse_pipex(t_shell *shell)
{	
	int i;

	i = 0;
	init_shell(shell);
	if (shell->pipex == 0)
	{	
		shell->exit = parse_no_pipes_line(shell);
		free_m(shell->args);
	}
	else
	{	
		create_pipes(shell);
		shell->exit = parse_line(shell, i);
		free(shell->p);
		free_m(shell->pipes);
	}
	free(shell->pid);
}
