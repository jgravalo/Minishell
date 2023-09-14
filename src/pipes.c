#include "../inc/minishell.h"

void	create_pipes(t_shell *shell)
{	
	int i;

	i = 0;
	shell->p = (t_pipe *)malloc(sizeof(t_pipe) * (shell->pipes));
	while (i < shell->pipes)
	{	
		pipe(shell->p[i].p);
		i++;
	}
}