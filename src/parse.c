/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/07 13:34:58 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_cmd_table(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipex + 1)
	{
		free(shell->struct_cmd[i]);
		i++;
	}
	free(shell->struct_cmd);
}

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
		i++;
	}
	if (shell->pipex == 0)
	{	
		shell->struct_cmd[0]->infile = -10;
		shell->struct_cmd[0]->outfile = -10;
		shell->readline = parse_redir(shell->readline, shell, 0);
		shell->struct_cmd[0]->args = ft_split_marks(shell->readline, ' ');
	}
}

void parse_pipex(t_shell *shell)
{	
	int i;

	i = 0;
	init_shell(shell);
	create_cmd_table(shell);
	if (!shell->struct_cmd[0]->args)
		return ;
	if (g_exit == 1)
	{	
		printf("entra aqui y sale\n");
		shell->exit = 1;
		return ;
	}
	if (shell->pipex == 0)
	{	
		parse_no_pipes_line(shell);
		recover_std(shell, 0);
		if (shell->struct_cmd[0]->args)
			free_m(shell->struct_cmd[0]->args);
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
	free(shell->redir_error);
	free(shell->inpipe);
	free(shell->outpipe);
	free(shell->pid);
	free_cmd_table(shell);
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
