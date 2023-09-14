#include "../inc/minishell.h"

void parent_close_but_one(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipes - 1)
	{
		close(shell->p[i].p[READ]);
		close(shell->p[i].p[WRITE]);
		i++;
	}
}
