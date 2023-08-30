/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/08/30 12:31:29 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void create_cmd_table(t_shell *shell)
{	
	int i;

	i = 0;
	shell->struct_cmd = (t_cmd **)malloc(sizeof (t_cmd *) * (shell->pipex + 2));
	while (i < shell->pipex + 1)
	{
		shell->struct_cmd[i] = (t_cmd *)malloc(sizeof (t_cmd));
		i++;
	}
	shell->struct_cmd[shell->pipex + 1] = NULL;
	i = 0;
	while (i < shell->pipex + 1)
	{	
		shell->struct_cmd[i]->infile = -10;
		shell->struct_cmd[i]->outfile = -10;
		shell->pipes[i] = parse_redir(shell->pipes[i], shell, i);
		shell->struct_cmd[i]->args = ft_split_marks(shell->pipes[i], ' ');
		i++;
	}

}

void parse_pipex(t_shell *shell)
{	
	int i;

	i = 0;
	init_shell(shell);
	if (shell->pipex == 0)
	{	
		parse_no_pipes_line(shell);
		recover_std(shell);
		if (shell->args)
			free_m(shell->args);
	}
	else
	{	
		create_pipes(shell);
		create_cmd_table(shell);
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
