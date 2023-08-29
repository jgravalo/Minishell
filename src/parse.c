/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/29 16:35:07 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void parse_pipex(t_shell *shell)
{	
	int i;

	i = 0;
	init_shell(shell);
	if (shell->pipex == 0)
	{	
		//printf("entra en no pipes\n");
		parse_no_pipes_line(shell);
		if (shell->args)
			free_m(shell->args);
	}
	else
	{	
		create_pipes(shell);
		parse_line(shell, i);
		parent_close(shell);
		shell->pid[shell->pipex + 1] = 0;
		set_signals(shell, shell->envp);
		free(shell->p);
		free(shell->pid_end);
		free_m(shell->pipes);
	}
	free(shell->pid);
}

void	parse_line(t_shell *shell, int i)
{	
	char	*tmp;

	check_pipe(shell, i);
	shell->pid[i] = fork();
	if (shell->pid[i] > 0)
		parent_routine(shell, i);
	if (shell->pid[i] == 0)
		child_routine(shell, i);
}
