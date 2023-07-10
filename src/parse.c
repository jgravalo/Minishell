#include "../inc/minishell.h"

int	parse_line(char *line, char **envp, t_pipe *in, t_pipe *out)
//int	parse_line(char *line, char **envp)
{
	char	**args;
	char	*cmd;
	pid_t	pid;
//	t_pipe	p;
	int		exit_code;
/*
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
*/
//	line = check_vars(line, envp);
//	write(1, line, ft_strlen(line));
//	write(1, "\n", 1);
//	args = ft_split_marks(line, ' ');
	/*
	int i;
	for (i = 0; args[i]; i++)
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, ", ", 2);
	}
	write(1, "\n", 1);
	*/
//	ft_strcmp(tmp, (char *){27, 91, 65});
//	exit = built_ins(args, envp);
	pid = fork();
	if (pid > 0)
		exit_code = set_signals(pid, envp);
	if (pid == 0)
	{	
		//fd = check_redir(args); //si hay redireccion, borrarla de la linea
		if (in != NULL)
		{
			dup2(in->p[0], 0);
			close(in->p[0]);
			close(in->p[1]);
//			test_pipe(in);
		}
		if (out != NULL)
		{
			dup2(out->p[1], 1);
			close(out->p[0]);
			close(out->p[1]);
		}
//		dup2(1, 2);
		args = ft_split_marks(line, ' ');
		cmd = file_cmd(args[0], envp); // error handling dentro de file_cmd
		if (cmd == NULL)
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
	free(shell.p);
	return (shell.exit);
}
