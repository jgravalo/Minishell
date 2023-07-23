/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/23 10:44:44 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	pid_t	pid;

	shell->args = ft_split_marks(shell->pipes[0], ' ');
	if (run_builtin(shell->args, envp) == 0)
	{
		free_m(shell->args);
		return (0);
	}		
	pid = fork();
	if (pid > 0)
		shell->exit = set_signals(shell, envp);
	if (pid == 0)
	{	
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea
		//tmp = parse_redir(line); // aplica las redirecciones (de momento solo de salida)
		//shell->args = ft_split_marks(tmp, ' ');
		cmd = file_cmd(shell->args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, shell->args, envp);
	}
	return(set_signals(shell, envp));
}