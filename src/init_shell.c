#include "../inc/minishell.h"

void init_shell(t_shell *shell)
{	
	shell->pipex = count_ascii(shell->readline, '|');
	if (shell->pipex > 0)
		shell->pipes = ft_split(shell->readline, '|');
	if (shell->pipex == 0)
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (2));
	else
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (shell->pipex + 1));
	shell->children = 0;
	shell->last_builtin = 0;
	shell->infd	= -1;
	shell->outfd = -1;
	shell->redir_type = -1;
}