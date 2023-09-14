#include  "../inc/minishell.h"

void execute_redir(t_shell *shell, t_cmd **cmd, int *i)
{
	//printf("i am child %d\n", getpid());
	heredoc(shell, cmd, i);

	exit(0);
}