#include  "../inc/minishell.h"

int	wait_for_children(t_shell *shell)
{	
	int status;
	
	if (shell->children == 1)
	{
		wait(&status);
		printf("sale de esperar\n");
	}
	else
	{
		while (shell->children)
		{	
			if (wait(&status) > 0)
			{	
				shell->children--;
				if (WIFEXITED(status) ) 
				{
					shell->exit = WEXITSTATUS(status);
					printf("exit status %d\n", shell->exit);
					break ;
				}
			}
		}
	}
	return (shell->exit);
}

void	handler(int signal)
{	
	if (signal == SIGINT)
		kill(0, SIGINT);
	else if (signal == SIGQUIT)
		kill(0, SIGQUIT);
	write(1, "\n", 1);
}

void	set_signals(t_shell *shell, char **envp)
{
	sigset_t			sigset;
	struct sigaction	sa;
	int					status;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaddset(&sigset, SIGINT);
	sigaction(SIGQUIT, &sa, NULL);
	sigaddset(&sigset, SIGQUIT);
	wait_for_children(shell);
}

void	parent_routine(t_shell *shell, int i)
{	
	shell->children++;
	if (i < shell->pipex)
		parse_line(shell, i + 1); 
}
