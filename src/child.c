#include  "../inc/minishell.h"

void child_routine(t_shell *shell, int i)
{	
/* 	shell->pipes[i] = parse_redir(shell->pipes[i], shell);
	shell->args = ft_split_marks(shell->pipes[i], ' '); */
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
		//printf("pipe de salida, proceso %d\n", getpid());
		close(shell->p[i].p[READ]);
		dup2(shell->p[i].p[WRITE], STDOUT_FILENO);
		close(shell->p[i].p[WRITE]);
		//printf("sale de pipe de salida, proceso %d\n", getpid());
	}
	if (shell->pipex > 1)
		close_fd(shell, i);
	if (shell->struct_cmd[i]->infile > -1 || shell->struct_cmd[i]->outfile > -1)
	{	
		//printf("entra en make redir\n");
		make_redir(shell, i);
	}
	if (check_builtin(shell->struct_cmd[i]->args) == 1)
	{	
		run_builtin(shell, i);
		exit(shell->exit);
	}
	shell->struct_cmd[i]->args[0] = file_cmd(shell, i); // error handling dentro de file_cmd
	if (ft_strcmp(shell->struct_cmd[i]->args[0], "empty") == 0)
		exit(0);
	else if (shell->struct_cmd[i]->args[0] == NULL)
		exit(shell->exit);
	execve(shell->struct_cmd[i]->args[0], shell->struct_cmd[i]->args, shell->envp);
}
