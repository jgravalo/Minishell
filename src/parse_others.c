/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 08:49:57 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	parse_ands(char *line, char **envp)
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
}

int	parse_no_pipes_line(t_shell *shell, char **envp)
{
	char	*cmd;
	char	*tmp;

	shell->args = ft_split_marks(shell->pipes[0], ' ');
	if (run_builtin(shell->args, envp) == 0)
	{	
		printf("countarr fuera de runbuiltin : %d\n", count_arr(envp));
		free_m(shell->args);
		return (0);
	}		
	shell->pid[0] = fork();
	if (shell->pid[0] > 0)
	{
		shell->pid[1] = 0;
		shell->children++;
		return(set_signals(shell, envp));
	}
	else
	{	
		tmp = parse_redir(shell->pipes[0]);
		shell->args = ft_split_marks(tmp, ' ');
		cmd = file_cmd(shell->args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, shell->args, envp);
		return (1);
	}
}
