#include  "../inc/minishell.h"

static	void create_pipes(t_shell *shell, t_cmd **cmd)
{	
	int i;

	i = 0;
	shell->p = (t_pipe *)malloc(sizeof(t_pipe) * (shell->pipes));
	while (i < shell->pipes)
	{	
		pipe(shell->p[i].p);
		i++;
	}
	shell->children = 0;
}

static void	fork_cmd(t_shell *shell, t_cmd **cmd, int *i)
{	
	(*i)++;
	cmd[*i]->pid = fork();
	shell->children++;
	if (cmd[*i]->pid > 0)
	{	
		if (*i < shell->pipes)
			fork_cmd(shell, cmd, i);
	}
}

void execute(t_shell *shell, t_cmd **cmd)
{	
	int i;
	int status;

	i = -1;
	if (!shell->pipes && check_builtin(cmd[0]->args))
	{	
		i++;
		execute_redir(shell, cmd, &i);
		builtin(shell, cmd, &i);
		return ;	
	}
	create_pipes(shell, cmd);
	fork_cmd(shell, cmd, &i);
	if (cmd[i]->pid == 0)
	{	
		execute_pipes(shell, cmd, i);
		execute_redir(shell, cmd, &i);
		if (builtin(shell, cmd, &i))
			exit(shell->exit);
		search(shell, cmd, &i);
		execve(cmd[i]->path, cmd[i]->args, shell->envp);
	}
	else
	{	
		parent_close(shell);
		parent_wait(shell, cmd);
	}
	
}