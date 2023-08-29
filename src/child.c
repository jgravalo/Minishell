#include  "../inc/minishell.h"

void child_routine(t_shell *shell, int i)
{	
	shell->pipes[i] = parse_redir(shell->pipes[i], shell);
	shell->args = ft_split_marks(shell->pipes[i], ' ');
	if (shell->inpipe == 1) // hay pipe de entrada
	{	
		//printf("pipe de entrada, proceso %d\n", getpid());
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
		//printf("sale de pipe de entrada, proceso %d\n", getpid());
	}
	if (shell->outpipe == 1) // hay pipe de salida
	{	
		printf("pipe de salida, proceso %d\n", getpid());
		close(shell->p[i].p[READ]);
		dup2(shell->p[i].p[WRITE], STDOUT_FILENO);
		close(shell->p[i].p[WRITE]);
		printf("sale de pipe de salida, proceso %d\n", getpid());
	}
	if (shell->pipex > 1)
		close_fd(shell, i);
	if (shell->redir_type != -1)
	{	
		printf("redir es %d, entra en make redir\n", shell->redir_type);
		make_redir(shell);
	}
	if (check_builtin(shell->args) == 1)
	{	
		run_builtin(shell);
		exit(shell->exit);
	}
	shell->cmd = file_cmd(shell); // error handling dentro de file_cmd
	if (ft_strcmp(shell->cmd, "empty") == 0)
	{	
		printf("hijo sale correctamente\n");
		exit(0);
	}
	else if (shell->cmd == NULL)
		exit(shell->exit);
	execve(shell->cmd, shell->args, shell->envp);
}
