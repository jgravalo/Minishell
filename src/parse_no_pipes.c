/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/04 10:45:55 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void handler(int sig)
{
	if (sig == SIGINT)
		kill(0, SIGINT);
}

static void fork_process(t_shell *shell)
{
	if (shell->pid[0] > 0)
	{	
		shell->pid[1] = 0;
		shell->children++;
		set_signals(shell, shell->envp);
	}
	else
	{	
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		if (shell->struct_cmd[0]->infile > -1 || shell->struct_cmd[0]->outfile > -1)
			make_redir(shell, 0);
		shell->struct_cmd[0]->args[0] = file_cmd(shell, 0);
		if (shell->struct_cmd[0]->args[0] == NULL)  
			exit(shell->exit);
		if (ft_strcmp(shell->struct_cmd[0]->args[0], "empty") == 0)
			exit(0);
		execve(shell->struct_cmd[0]->args[0], shell->struct_cmd[0]->args, shell->envp);
	}
}

void	parse_no_pipes_line(t_shell *shell)
{
	int i;
	
	i = 0;
	if (shell->redir_error[0]) // algo ha ido mal y escribimos errno y retornamos
	{	
		cmd_error(shell->error_tmp, errno, 1);
		return ;
	}
	if (shell->readline)
	{	
		while (shell->struct_cmd[0]->args[i])
			i++;
		change_var(shell, "_", shell->struct_cmd[0]->args[i - 1]);
		if (built_in(shell, 0) == 1) 
			return ;
	}
	shell->pid[0] = fork();
	fork_process(shell); // aligeramos lineas en función.
}
