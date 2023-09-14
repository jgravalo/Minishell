#include  "../inc/minishell.h"

static void mid_cmd(t_shell *shell, int i)
{	
	int store;

	store = i;
	i++;
	while (i < shell->pipes)
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

static void close_pipes(t_shell *shell, int i)
{	
	if (i == 0)
	{	
		i++;
		while (i < shell->pipes)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i++;	
		}
	}
	else if (i == shell->pipes)
	{	
		i -= 2;
		while (i >= 0)
		{
			close(shell->p[i].p[READ]);
			close(shell->p[i].p[WRITE]);
			i--;
		}
	}
	else
		mid_cmd(shell, i);
}

static void	check_pipe(t_shell *shell, t_cmd **cmd, int i)
{
	if (i == 0)
	{
		cmd[i]->in_pipe = 0;
		cmd[i]->out_pipe = 1;
	}
	else if (i == shell->pipes)
	{	
		cmd[i]->in_pipe = 1;
		cmd[i]->out_pipe = 0;
	}
	else 
	{
		cmd[i]->in_pipe = 1;
		cmd[i]->out_pipe = 1;
	}
}

static void handle_inpipe(t_shell *shell, t_cmd **cmd, int i)
{
	if (cmd[i]->in_pipe == 1) // hay pipe de entrada
	{	
		close(shell->p[i - 1].p[WRITE]);
		dup2(shell->p[i - 1].p[READ], STDIN_FILENO);
		close(shell->p[i - 1].p[READ]);
	}
}

static void handle_outpipe(t_shell *shell, t_cmd **cmd, int i)
{
	if (cmd[i]->out_pipe == 1) // hay pipe de salida
	{	
		close(shell->p[i].p[READ]);
		dup2(shell->p[i].p[WRITE], STDOUT_FILENO);
		close(shell->p[i].p[WRITE]);
	}
}

void execute_pipes(t_shell *shell, t_cmd **cmd, int i)
{
	check_pipe(shell, cmd, i);
	handle_inpipe(shell, cmd, i);
	handle_outpipe(shell, cmd, i);
	if (shell->pipes > 1)
		close_pipes(shell, i);
}