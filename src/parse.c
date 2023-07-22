/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:34:38 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/22 17:44:27 by theonewhokn      ###   ########.fr       */
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
static void	check_pipe(t_shell *shell, int i)
{
	if (i == 0)
	{	
		shell->inpipe = 0;
		shell->outpipe = 1;
	}
	else if (i == shell->pipex)
	{	
		shell->inpipe = 1;
		shell->outpipe = 0;
	}
	else 
	{
		shell->inpipe = 1;
		shell->outpipe = 1;
	}
}

static void parent_close(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipex)
	{
		close(shell->p[i].p[READ]);
		close(shell->p[i].p[WRITE]);
		//printf("cierra pipe %d\n", i);
		i++;
	}
}

static void close_fd(t_shell *shell, int i)
{	
	int store;

	if (i == 0)
	{	
		//printf("proces %d entra en primer comando\n", getpid());
		i++;
		while (i < shell->pipex)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i++;	
		}
	}
	else if (i == shell->pipex)
	{	
		//printf("proces %d entra en ultimo comando aqui\n", getpid());
		i -= 2;
		while (i >= 0)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i--;
		}
	}
	else
	{	
		store = i;
		i++;
		while (i < shell->pipex)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i++;
		}
		i = store;
		i -= 2;
		while (i >= 0)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i--;
		}
	}
}

int	parse_line(t_shell *shell, char **envp, int i)
{	
	char	*cmd;
	char	*tmp;
	pid_t	pid;
	int		inpipe;
	int		outpipe;

	inpipe = -1;
	outpipe = -1;
	check_pipe(shell, i);
	shell->args = ft_split_marks(shell->pipes[i], ' ');
	if (check_builtin(shell->args, envp) == 1 && shell->outpipe == 0) // es ultimo proceso y si es built in se corre en la misma shell
	{	
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
		if (run_builtin(shell->args, envp) == 0)  // corremos built in y retornamos, último proceso
			return (0);
	}
	pid = fork();
	if (pid > 0)
	{	
		free_m(shell->args);
		shell->children++;
		if (i < shell->pipex)
			parse_line(shell, envp, i + 1); 
		parent_close(shell);
	}
	if (pid == 0)
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
		//tmp = parse_redir(line); // aplica las redirecciones (de momento solo de salida)
		cmd = file_cmd(shell->args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL) // file_cmd ya mide errores
			exit(1);
		execve(cmd, shell->args, envp);
	}
	while (shell->children)
	{	
		pid = waitpid(-1, &shell->exit, WNOHANG);
		if (pid > 0)
			shell->children--;
	}
	/* exit_code = set_signals(pid, envp);
	exit_code = WEXITSTATUS(exit_code); */
	return (shell->exit);
}

int parse_pipex(char *line, char **envp)
{	
	t_shell	shell;
	int i;

	i = 0;
	shell.pipex = count_ascii(line, '|');
	shell.pipes = ft_split(line, '|');
	shell.children = 0;
	if (shell.pipex == 0)
		shell.exit = parse_no_pipes_line(shell.pipes[0], envp); // si no hay pipes, built ins siempre correran en la misma shell
	else
	{	
		/*Se crean las pipes antes, porque si pipeline es larga da error, ya que procesos quieren
		cerrar filedescriptors de pipes que aún no están generadas*/
		shell.p = (t_pipe *)malloc(sizeof(t_pipe) * (shell.pipex));
		while (i < shell.pipex)
		{	
			pipe(shell.p[i].p);
			i++;
		}
		i = 0; // resetamos la i a cero, ya que esencial para la recursividad de parse_line
		shell.exit = parse_line(&shell, envp, i);
		free(shell.p);
	}
	free_m(shell.pipes);
	return (shell.exit);
}
