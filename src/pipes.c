#include "../inc/minishell.h"

void	check_pipe(t_shell *shell, int i)
{
	if (i == 0)
	{	
		//printf("i es %d, pipe de salida\n", i);
		shell->inpipe[i] = 0;
		shell->outpipe[i] = 1;
	}
	else if (i == shell->pipex)
	{	
		//printf("i es %d, pipe de entrada\n", i);
		shell->inpipe[i] = 1;
		shell->outpipe[i] = 0;
	}
	else 
	{
		shell->inpipe[i] = 1;
		shell->outpipe[i] = 1;
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