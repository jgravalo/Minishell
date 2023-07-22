#include "../inc/minishell.h"

static void mid_cmd(t_shell *shell, int i)
{
	int store;

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

void close_fd(t_shell *shell, int i)
{	
	if (i == 0)
	{	
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

void parent_close_but_one(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipex - 1)
	{
		close(shell->p[i].p[READ]);
		close(shell->p[i].p[WRITE]);
		i++;
	}
}

void parent_close(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipex)
	{
		close(shell->p[i].p[READ]);
		close(shell->p[i].p[WRITE]);
		i++;
	}
}