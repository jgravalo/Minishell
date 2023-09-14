#include "../inc/minishell.h"

void empty_old_pwd(t_shell *shell)
{	
	shell->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	shell->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	shell->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	shell->s_cmd[0]->args[0] = ft_strdup("unset");
	shell->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	shell->s_cmd[0]->args[2] = NULL;
	unset(shell, shell->s_cmd, 0);
	free_m(shell->s_cmd[0]->args);
	shell->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	shell->s_cmd[0]->args[0] = ft_strdup("export");
	shell->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	shell->s_cmd[0]->args[2] = NULL;
	export(shell, shell->s_cmd, 0);
	free_m(shell->s_cmd[0]->args);
	free(shell->s_cmd[0]);
	free(shell->s_cmd);
	shell->old_pwd = ft_strdup("");
}

void alloc_envp(t_shell *shell, char **envp)
{	
	int		i;
	char	buffer[100];

	shell->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	empty_old_pwd(shell);
	if (getenv("SHELL") != NULL)
		change_var(shell, "SHELL", getcwd(buffer, 100));
	if (getenv("SHLVL") != NULL)
		change_var(shell, "SHLVL", ft_itoa(ft_atoi(getenv("SHLVL")) + 1));
}

int	change_var(t_shell *shell, char *var, char *content)
{
	int		var_num;
	char	*tmp;

	var_num = search_var_num(var, shell->envp);
	if (var_num < 0)
		return (1);
	tmp = ft_strjoin(var, "=");
	free(shell->envp[var_num]);
	shell->envp[var_num] = ft_strjoin(tmp, content);
	if (ft_strlen(content) == 0)
		shell->envp[var_num] = ft_strdup(shell->envp[var_num]);
	free(tmp);
	return (0);
}