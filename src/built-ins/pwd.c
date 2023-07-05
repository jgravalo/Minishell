#include "../../inc/minishell.h"

int pwd(char **envp)
{
	char	*pwd;

	pwd = search_var("PWD", envp);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}
