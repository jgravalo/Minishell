#include "../inc/minishell.h"

static void fill_pid_end(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipex + 1)
	{
		shell->pid_end[i] = 0;
		i++;
	}
	shell->pid_end[i] = -10;
}

void init_shell(t_shell *shell)
{	
	shell->pipex = count_ascii(shell->readline, '|');
	if (shell->pipex > 0)
		shell->pipes = ft_split(shell->readline, '|');
	if (shell->pipex == 0)
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (2));
	else
	{
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (shell->pipex + 2));
		shell->pid_end = (int *)malloc(sizeof (int) * (shell->pipex + 2));
		fill_pid_end(shell);
	}
	shell->children = 0;
	shell->last_builtin = 0;
	shell->infd	= -1;
	shell->outfd = -1;
	shell->redir_type = -1;
	shell->exit = 0;
	shell->delimiter = NULL;
	shell->heredoc_quoted = -1;
}