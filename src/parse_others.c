/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/31 09:05:25 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

/* int	parse_ands(char *line, char **envp)
{
	char	**ands;
	int		i;
	int		exit;

	ands = ft_split(line, '&');
	i = 0;
	while (ands[i])
	{
		exit = parse_pipex(ands[i], envp);
		i++;
	}
	return (exit);
}

int	parse_ors(char *line, char **envp)
{
	char	**ors;
	int		i;
	int		exit;

	ors = ft_split(line, '|');
	i = 0;
	while (ors[i])
	{
		exit = parse_ands(ors[i], envp);
		if (exit == 0)
			break ;
		i++;
	}
	return (exit);
} */

int	parse_no_pipes_line(t_shell *shell)
{
	char 	*cmd;

	shell->readline = parse_redir(shell->readline, shell);
	printf("after splitredir: %s\n", shell->readline);
	shell->args = ft_split_marks(shell->readline, ' ');
	if (shell->redir_type != -1)
		make_redir(shell);
	if (run_builtin(shell) == 0)
	{
		if (shell->redir_type == 0)
			dup2(shell->saved_stdin, 0);
		if (shell->redir_type == 1)
			dup2(shell->saved_stdout, 1);
		return (0);	
	}
		
	shell->pid[0] = fork();
	if (shell->pid[0] > 0)
	{
		shell->pid[1] = 0;
		shell->children++;
		return(set_signals(shell, shell->envp));
	}
	else
	{	
		cmd = file_cmd(shell->args[0], shell->envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, shell->args, shell->envp);
		return (1);
	}
}
