/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 11:52:23 by theonewhokn      ###   ########.fr       */
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
	shell->readline = parse_redir(shell->readline, shell);
	if (shell->exit != 0)
		return ;
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
	shell->cmd = file_cmd(shell);
	if (ft_strcmp(shell->cmd, "empty") == 0)
	{	
		if (shell->redir_type != -1)
		{	
			make_redir(shell);
			recover_std(shell);
		}
		return ;
	}
	else if (shell->cmd == NULL)
		return ;
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
		signal(SIGQUIT, handler);
		if (shell->redir_type != -1)
			make_redir(shell);
		execve(shell->cmd, shell->args, shell->envp);
	}
}
