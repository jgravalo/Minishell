/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/26 15:28:59 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
typedef struct s_cmd
{
int pipex;
char **pipes;
t_pipe *pipe;
char **envp
} t_cmd;

int parse_line(t_cmd *c, int n, t_pipe *in, t_pipe *out)
{
pid_t pid;
pid = fork();
if (pid > 0)
{
exit = set_signals(pid, c->envp);
exit = builtins();
n++;
if (out != NULL)
exit = parse_line(&cmd, n, c->p[n - 1], c->p[n]);
}
if (pid == 0)
{
if (in != NULL)
dup_and_close(in, 0);
if (out != NULL)
dup_and_close(out, 1);
tmp = parse_redir(line);
args = ft_split_marks(tmp, ' ');
cmd = file_cmd(args[0], c->envp);
execve(cmd, args, c->envp);
}
return (exit);
}
*/

/* static int first_pipe(t_shell *shell, char **envp)
{
	shell->p = (t_pipe *)malloc(sizeof(t_pipe) * (shell->pipex + 1));
	pipe(shell->p[0].p);
	shell->exit = parse_line(shell->pipes[0], envp, NULL, &shell->p[0]); //primer pipe
	close(shell->p[0].p[1]); // cierras la salida/escritura del pipe
	return (shell->exit);
} */

/* static int	middle_pipe(t_shell *shell, char **envp, int *i)
{
	pipe(shell->p[*i].p);
	shell->exit = parse_line(shell->pipes[*i],
			envp, &shell->p[*i - 1], &shell->p[*i]);
	close(shell->p[*i - 1].p[0]);
	close(shell->p[*i].p[1]);
	(*i)++;
	return (shell->exit);
} */

/* static int	handle_pipes(t_shell *shell, char **envp)
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
} */

	/* if (shell->outpipe == 0 && check_builtin(shell->args, envp) == 1) // es ultimo proceso y si es built in se corre en la misma shell
	{
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
		if (shell->pipex > 1)
			parent_close_but_one(shell);
		if (run_builtin(shell->args, envp) == 0)
		{	
			free_m(shell->args);
			return (wait_for_children(shell));	
		}			
	} */

static void	parent_routine(t_shell *shell, char **envp, int i)
{
	free_m(shell->args);
	shell->children++;
	if (i < shell->pipex)
		parse_line(shell, envp, i + 1); 
}

static void child_routine(t_shell *shell, char **envp, int i)
{
	if (shell->inpipe == 1) // hay pipe de entrada
	{	
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
	}
	if (shell->outpipe == 1) // hay pipe de salida
	{	
		close(shell->p[i].p[READ]);
		dup2(shell->p[i].p[WRITE], STDOUT_FILENO);
		close(shell->p[i].p[WRITE]);
	}
	if (shell->pipex > 1)
		close_fd(shell, i);
	char *tmp = parse_redir(shell->pipes[i]);
	shell->args = ft_split_marks(tmp, ' ');
	if (run_builtin(shell->args, envp) == 0)
		exit(1);
	shell->cmd = file_cmd(shell->args[0], envp); // error handling dentro de file_cmd
	if (shell->cmd == NULL) // file_cmd ya mide errores
		exit(1);
	execve(shell->cmd, shell->args, envp);
}

int	parse_line(t_shell *shell, char **envp, int i)
{	
	char	*tmp;

	check_pipe(shell, i);
	shell->args = ft_split_marks(shell->pipes[i], ' ');
	/* comentado de momento (en l.89), hay que revisar si efectivamente vale la pena complicarse, 
	no es tan claro que si el ultimo proceso de una pipeline es un builtin, lo haga la misma shell*/
	shell->pid[i] = fork();
	if (shell->pid[i] > 0)
		parent_routine(shell, envp, i);
	if (shell->pid[i] == 0)
		child_routine(shell, envp, i);
	parent_close(shell);
	shell->pid[i] = 0;
	return (set_signals(shell, envp));
	/* exit_code = set_signals(pid, envp);
	exit_code = WEXITSTATUS(exit_code); */
}

static void init_shell(t_shell *shell, char *line)
{
	shell->pipex = count_ascii(line, '|');
	shell->pipes = ft_split(line, '|');
	if (shell->pipex == 0)
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (2));
	else
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (shell->pipex + 1));
	shell->children = 0;
	shell->last_builtin = 0;
}

int parse_pipex(char *line, char **envp)
{	
	t_shell	shell;
	int i;

	i = 0;
	init_shell(&shell, line);
	if (shell.pipex == 0)
	{	
		shell.exit = parse_no_pipes_line(&shell, envp); // si no hay pipes, built ins siempre correran en la misma shell
		free_m(shell.args);
	}
	else
	{	
		/*Se crean las pipes antes, porque si pipeline es larga da error, ya que procesos quieren
		cerrar filedescriptors de pipes que aún no están generadas*/
		create_pipes(&shell);
		shell.exit = parse_line(&shell, envp, i);
		free(shell.p);
	}
	free(shell.pid);
	free_m(shell.pipes);
	return (shell.exit);
}
