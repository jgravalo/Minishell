#include "../../inc/minishell.h"

int pwd(char **envp)
{
	int		env;
	char	*pwd;

	env = search_var("PWD", envp);
	pwd = ft_strchr(envp[env], '/');
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	pwd(envp);
	if (!argv || !argc)
		return (0);
	return (0);
}
