/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 10:29:42 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void handler(int sig)
{
	if (sig == SIGINT)
		kill(0, SIGINT);
}

void	parse_no_pipes_line(t_shell *shell)
{
	char 	*cmd;

	shell->readline = parse_redir(shell->readline, shell);
	//printf("line after parse redir es %s\n", shell->readline);
	shell->args = ft_split_marks(shell->readline, ' ');
	//printf("sale de aqui sin problema\n");
	if (check_builtin(shell->args) == 1)
	{	
		if (shell->redir_type != -1)
			make_redir(shell);
		run_builtin(shell);
		recover_std(shell);
		return ;
	}
	shell->pid[0] = fork();
	if (shell->pid[0] > 0)
	{	
		shell->pid[1] = 0;
		shell->children++;
		set_signals(shell, shell->envp);
	}
	else
	{	
		signal(SIGINT, handler);
		cmd = file_cmd(shell);
		if (ft_strcmp(cmd, "empty") == 0)
		{	
			if (shell->redir_type != -1)
				make_redir(shell);
			exit(0);
		}
		if (shell->redir_type != -1)
			make_redir(shell);
		execve(cmd, shell->args, shell->envp);
	}
}
