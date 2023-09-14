#include  "../inc/minishell.h"

static void check_inpipe(t_shell *shell, int i)
{
	if (shell->inpipe[i] == 1) // hay pipe de entrada
	{	
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
	}
}

static void check_outpipe(t_shell *shell, int i)
{
	if (shell->outpipe[i] == 1) // hay pipe de salida
	{	
		close(shell->p[i].p[READ]);
		dup2(shell->p[i].p[WRITE], STDOUT_FILENO);
		close(shell->p[i].p[WRITE]);
	}
}

void child_routine(t_shell *shell, int i)
{	
	if (shell->struct_cmd[i]->redir)
		set_redir(shell, i);
	if (shell->redir_error[i]) // algo ha ido mal y escribimos errno y salimos
	{	
		cmd_error(shell->error_tmp, errno, 1);
		exit(1);
	}
	//shell->struct_cmd[i]->args = ft_split_marks(shell->pipes[i], ' ');
	check_inpipe(shell, i);
	check_outpipe(shell, i);
	if (shell->pipes > 1)
		close_fd(shell, i);
	if (shell->struct_cmd[i]->infile > -1 || shell->struct_cmd[i]->outfile > -1)
		make_redir(shell, i);
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
