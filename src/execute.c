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

static void child(t_shell *shell, t_cmd **cmd, int *i)
{
	printf("i am child %d\n", getpid());
	exit(0);
}

static void	fork_cmd(t_shell *shell, t_cmd **cmd, int *i)
{	
	(*i)++;
	//check_pipe(shell, i);
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

	i = -1;
	create_pipes(shell, cmd);
	fork_cmd(shell, cmd, &i);
	if (cmd[i]->pid == 0)
		child(shell, cmd, &i);
	
}