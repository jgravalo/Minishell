#include "../inc/minishell.h"

void empty_old_pwd(t_shell *shell)
{	
	shell->args = (char **)malloc(sizeof (char *) * 3);
	shell->args[0] = ft_strdup("unset");
	shell->args[1] = ft_strdup("OLDPWD");
	shell->args[2] = NULL;
	unset(shell);
	free_m(shell->args);
	shell->args = (char **)malloc(sizeof (char *) * 3);
	shell->args[0] = ft_strdup("export");
	shell->args[1] = ft_strdup("OLDPWD");
	shell->args[2] = NULL;
	export(shell);
	free_m(shell->args);
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