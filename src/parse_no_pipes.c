/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/29 15:08:22 by jgravalo         ###   ########.fr       */
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
		if (shell->redir_type != -1)
			make_redir(shell);
		shell->cmd = file_cmd(shell);
		if (ft_strcmp(shell->cmd, "empty") == 0)
			exit(0);
		else if (shell->cmd == NULL)  
			exit(shell->exit);
		execve(shell->cmd, shell->args, shell->envp);
	}
}

void	parse_no_pipes_line(t_shell *shell)
{
	int i;

	shell->readline = parse_redir(shell->readline, shell); 
	if (shell->exit != 0) // algo ha ido mal y retornamos, mensaje de error ya se ha mostrado con cmd_error.
		return ;
	shell->args = ft_split_marks(shell->readline, ' ');
	i = 0;
	while (shell->args[i])
		i++;
	change_var(shell, "_", shell->args[i - 1]);
	if (built_in(shell) == 1)   // agrupamos gestión de built in en una función
		return ;
	shell->pid[0] = fork();
	fork_process(shell); // aligeramos lineas en función.
}
