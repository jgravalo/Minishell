#include "../../inc/minishell.h"

int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	if (!argc)
		return (0);
	env(envp);
	return (0);
}
