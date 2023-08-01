/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/01 17:56:31 by dtome-pe         ###   ########.fr       */
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

void parse_pipex(t_shell *shell)
{	
	int i;

	i = 0;
	init_shell(shell);
	if (shell->pipex == 0)
	{	
		parse_no_pipes_line(shell);
		free_m(shell->args);
	}
	else
	{	
		create_pipes(shell);
		parse_line(shell, i);
		free(shell->p);
		free_m(shell->pipes);
	}
	free(shell->pid);
}
