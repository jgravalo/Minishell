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
	int		i;
	char	buffer[100];

	shell->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
//	env(envp);
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	printf("%s\n", shell->envp[i - 1]);
//	env(shell->envp);
	empty_old_pwd(shell);
	change_var(shell, "SHELL", getcwd(buffer, 100));
//	env(shell->envp);
}

void	change_var(t_shell *shell, char *var, char *content)
{
	int		var_num;
	char	*tmp;

	var_num = search_var_num(var, shell->envp);
	if (var_num < 0)
		return ;
	tmp = ft_strjoin(var, "=");
	free(shell->envp[var_num]);
	shell->envp[var_num] = ft_strjoin(tmp, content);
	free(tmp);
}
