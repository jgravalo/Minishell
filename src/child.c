#include  "../inc/minishell.h"

void child_routine(t_shell *shell, int i)
{	
	shell->readline = parse_redir(shell->pipes[i], shell);
	shell->args = ft_split_marks(shell->pipes[i], ' ');
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
	if (check_builtin(shell->args) == 1)
	{	
		run_builtin(shell);
		exit(shell->exit);
	}
	shell->cmd = file_cmd(shell->args[0], shell->envp); // error handling dentro de file_cmd
	if (shell->cmd == NULL) // file_cmd ya mide errores
		exit(1);
	execve(shell->cmd, shell->args, shell->envp);
}