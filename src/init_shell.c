#include "../inc/minishell.h"

static void fill_pid_end(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipes + 1)
	{
		shell->pid_end[i] = 0;
		i++;
	}
	shell->pid_end[i] = -10;
}

static void fill_redir_error(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipes + 1)
	{
		shell->redir_error[i] = 0;
		i++;
	}
}

static void fill_pipe_check(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->pipes + 1)
	{
		shell->inpipe[i] = 0;
		shell->outpipe[i] = 0;
		i++;
	}
}

void init_shell(t_shell *shell)
{	
	shell->pipes = count_ascii(shell->readline, '|');
	if (shell->pipes > 0)
		shell->pipes = ft_split(shell->readline, '|');
	if (shell->pipes == 0)
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (2));
	else
	{
		shell->pid = (pid_t *)malloc(sizeof (pid_t) * (shell->pipes + 2));
		shell->pid_end = (int *)malloc(sizeof (int) * (shell->pipes + 2));
		fill_pid_end(shell);
	}
	shell->args = NULL;
	shell->here_tmp = "/tmp/heretmp";
	shell->children = 0;
	shell->last_builtin = 0;
	shell->infd	= -1;
	shell->outfd = -1;
	shell->redir_type = -1;
	shell->delimiter = NULL;
	shell->heredoc_quoted = -1;
	shell->inpipe = (int *)malloc(sizeof (int) * (shell->pipes + 1));
	shell->outpipe = (int *)malloc(sizeof (int) * (shell->pipes + 1));
	fill_pipe_check(shell);
	shell->redir_error = (int *)malloc(sizeof (int) *(shell->pipes + 1));
	fill_redir_error(shell);
}
