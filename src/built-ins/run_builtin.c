# include "../../inc/minishell.h"

int run_cd(char **args, char **envp)
{	
	if (ft_strcmp(args[0], "cd") == 0)
	{
		cd(args[1], envp);
		return (0);
	}
	else
		return (1);
}

int run_builtin(char **args, char **envp)
{
	if (ft_strcmp(args[0], "echo") == 0)
	{
		echo(args);
		return (0);
	}
	else if (ft_strcmp(args[0], "env") == 0)
	{
		env(envp);
		return (0);
	}
	/* else if (ft_strcmp(args[0], "export") == 0)
	{
		export(args, envp);
		return (0);
	} */
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		pwd(envp);
		return (0);
	}
	/* else if (ft_strcmp(args[0], "unset") == 0)
	{
		unset(var, envp);
		return (0);
	} */
	else
		return (1);
}