#include "../inc/minishell.h"

void	check_pipe(t_shell *shell, int i)
{
	if (i == 0)
	{	
		shell->inpipe = 0;
		shell->outpipe = 1;
	}
	else if (i == shell->pipex)
	{	
		shell->inpipe = 1;
		shell->outpipe = 0;
	}
	else 
	{
		shell->inpipe = 1;
		shell->outpipe = 1;
	}
}

void	create_pipes(t_shell *shell)
{	
	int i;

	i = 0;
	shell->p = (t_pipe *)malloc(sizeof(t_pipe) * (shell->pipex));
	while (i < shell->pipex)
	{	
		pipe(shell->p[i].p);
		i++;
	}
}