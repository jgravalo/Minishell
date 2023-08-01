#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	t_shell				shell;

	alloc_envp(&shell, envp);
	if (!argc && !argv && !envp)
		return (0);
	new_shell(&shell);
	return (shell.exit);
}	