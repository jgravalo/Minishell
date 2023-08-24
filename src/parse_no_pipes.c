/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/24 19:21:12 by theonewhokn      ###   ########.fr       */
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
			make_redir(shell, NULL);     // no recuperamos stdin o stdout porque es hijo y se va al execve
		execve(shell->cmd, shell->args, shell->envp);
	}
}

void	parse_no_pipes_line(t_shell *shell)
{
	shell->readline = parse_redir(shell->readline, shell); 
	if (shell->exit != 0) // algo ha ido mal y retornamos, mensaje de error ya se ha mostrado con cmd_error.
		return ;
	shell->args = ft_split_marks(shell->readline, ' ');
	if (built_in(shell) == 1)   // agrupamos gestión de built in en una función
		return ;
	shell->cmd = file_cmd(shell);
	if (ft_strcmp(shell->cmd, "empty") == 0) // si file_cmd ha recibido linea vacia, es que solo había redir en la linea.
	{	
		make_redir(shell, "empty");
		recover_std(shell); // recuperamos stdin o stdout, ya que es proceso padre.
		return ;
	}
	else if (shell->cmd == NULL)  
		return ;
	shell->pid[0] = fork();
	fork_process(shell); // aligeramos lineas en función.
}
