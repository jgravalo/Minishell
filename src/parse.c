/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/19 18:17:11 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	dup_and_close(t_pipe *pipe, int mode)
{
	dup2(pipe->p[mode], mode);
	close(pipe->p[0]);
	close(pipe->p[1]);
}

int	parse_line(char *line, char **envp, t_pipe *in, t_pipe *out)
{
	char	**args;
	char	*cmd;
	char	*tmp;
	pid_t	pid;
	int		exit_code;

	args = ft_split_marks(line, ' ');
	if (check_builtin(args, envp) == 1 && out == NULL) // es ultimo proceso y si es built in se corre en la misma shell
	{
		dup_and_close(in, 0); // gestionamos entrada pipe
		if (run_builtin(args, envp) == 0)  // corremos built in y retornamos, último proceso
			return (0);
	}
	pid = fork();
	if (pid > 0)
		exit_code = set_signals(pid, envp);
	if (pid == 0)
	{	
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea
		if (in != NULL)
			dup_and_close(in, 0);
		if (out != NULL)
			dup_and_close(out, 1);
		tmp = parse_redir(line); // aplica las redirecciones (de momento solo de salida)
		args = ft_split_marks(tmp, ' ');
		cmd = file_cmd(args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, args, envp);
	}
//	test_pipe(out);
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}

static int first_pipe(t_shell *shell, char **envp)
{
	shell->p = (t_pipe *)malloc(sizeof(t_pipe) * (shell->pipex + 1));
	pipe(shell->p[0].p);
	shell->exit = parse_line(shell->pipes[0], envp, NULL, &shell->p[0]); //primer pipe
	close(shell->p[0].p[1]); // cierras la salida/escritura del pipe
	return (shell->exit);
}

static int	middle_pipe(t_shell *shell, char **envp, int *i)
{
	pipe(shell->p[*i].p);
	shell->exit = parse_line(shell->pipes[*i],
			envp, &shell->p[*i - 1], &shell->p[*i]);
	close(shell->p[*i - 1].p[0]);
	close(shell->p[*i].p[1]);
	(*i)++;
	return (shell->exit);
}

static int	handle_pipes(t_shell *shell, char **envp)
{
	int	i;

	i = 1;
	if (first_pipe(shell, envp) == -1)
		return (-1);
	while (i < shell->pipex - 1)
	{
		if (middle_pipe(shell, envp, &i) == -1) 
			return (-1);
	}
	shell->exit = parse_line(shell->pipes[i], envp, &shell->p[i - 1], NULL); // ultimo proceso correra en misma shell si es built in
	close(shell->p[i - 1].p[0]);
	free(shell->p);
	return (shell->exit);
}

int parse_pipex(char *line, char **envp)
{	
	t_shell	shell;

	shell.pipex = count_ascii(line, '|');
	shell.pipes = ft_split(line, '|');
	if (shell.pipex == 0)
		shell.exit = parse_no_pipes_line(shell.pipes[0], envp); // si no hay pipes, built ins siempre correran en la misma shell
	else 
		shell.exit = handle_pipes(&shell, envp);
	free_m(shell.pipes);
	return (shell.exit);
}
