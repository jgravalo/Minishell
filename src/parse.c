#include "../inc/minishell.h"

static void dup_and_close(t_pipe *pipe, int mode)
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

//	ft_strcmp(tmp, (char *){27, 91, 65});
//	exit = built_ins(args, envp);
	args = ft_split_marks(line, ' ');
	if(run_cd(args, envp) == 0) // éxito en ejecutar cd, que no genera proceso hijo.
			return (0); 
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
		if (run_builtin(args, envp) == 0)
			exit (0);
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

static int middle_pipe(t_shell *shell, char **envp, int *i)
{
	pipe(shell->p[*i].p);
	shell->exit = parse_line(shell->pipes[*i], envp, &shell->p[*i - 1], &shell->p[*i]);// pipes intermedios
	close(shell->p[*i - 1].p[0]);
	close(shell->p[*i].p[1]);
	(*i)++;
	return (shell->exit);
}

static int handle_pipes(t_shell *shell, char **envp)
{	
	int i;

	i = 1;
	if(first_pipe(shell, envp) == -1) // error handling 
		return (-1);
	while (i < shell->pipex - 1)
	{
		if (middle_pipe(shell, envp, &i) == -1) // error handling 
			return (-1);
	}
	shell->exit = parse_line(shell->pipes[i], envp, &shell->p[i - 1], NULL); //ultimo pipe
	close(shell->p[i - 1].p[0]);
	free(shell->p);
	return (shell->exit);
}

int parse_pipex(char *line, char **envp)
{	
	t_shell shell;

	shell.pipex = count_ascii(line, '|');
	shell.pipes = ft_split(line, '|');
	if (shell.pipex == 0)
		shell.exit = parse_line(shell.pipes[0], envp, NULL, NULL); //sin pipe
	else 
		shell.exit = handle_pipes(&shell, envp);
	free_m(shell.pipes);
	return (shell.exit);
}
