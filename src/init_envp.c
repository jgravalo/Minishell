#include "../inc/minishell.h"

void empty_old_pwd(t_shell *shell)
{	
	shell->args = malloc(sizeof (char *) * 2);
	shell->args[0] = malloc (sizeof (char) * 6);
	shell->args[0] = "unset";
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[1] = "OLDPWD";
	shell->args[2] = NULL;
	unset(shell);
	//free_m(shell->args);
	shell->args = malloc(sizeof (char *) * 2);
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[0] = "export";
	shell->args[0] = malloc (sizeof (char) * 7);
	shell->args[1] = "OLDPWD";
	shell->args[2] = NULL;
	export(shell);
	//free_m(shell->args);
}

void alloc_envp(t_shell *shell, char **envp)
{	
	int i;

	shell->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	empty_old_pwd(shell);
}