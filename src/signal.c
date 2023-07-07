# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
#include "../inc/minishell.h"

pid_t	fg_pid;

void handler(int signal)
{
	if (signal == SIGINT)
	{	
		kill(fg_pid, SIGTERM);
	}
}

int set_signals(int pid, char **envp)
{
	sigset_t			sigset;
	struct sigaction	sa;
	int					status;

	fg_pid = pid;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaddset(&sigset, SIGINT);
	waitpid(0, &status, 0);
	if(WIFSIGNALED(status))
	{	
		write(1, "\n", 1);
		new_shell(envp);
		return (0);
	}		
	else
		return (status);
}