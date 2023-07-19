/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/19 18:12:59 by theonewhokn      ###   ########.fr       */
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

int	parse_no_pipes_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	char	*tmp;
	pid_t	pid;
	int		exit_code;

	args = ft_split_marks(line, ' ');
	if (run_builtin(args, envp) == 0) 
			return (0);
	pid = fork();
	if (pid > 0)
		exit_code = set_signals(pid, envp);
	if (pid == 0)
	{	
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea
		tmp = parse_redir(line); // aplica las redirecciones (de momento solo de salida)
		args = ft_split_marks(tmp, ' ');
		cmd = file_cmd(args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, args, envp);
	}
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}