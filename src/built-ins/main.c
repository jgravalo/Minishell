#include "../../inc/minishell.h"
#include "builtins.h"

int built_ins(char **argv, char **envp)
{
	int out;

	out = 0;
	printf("%s\n", argv[1]);
	if (ft_strcmp(argv[1], "cd") == 0)
	{
		pwd(envp);
		out = cd(argv[1]);
		pwd(envp);
	}
	else if (ft_strcmp(argv[1], "echo") == 0)
		out = echo(++argv);
	else if (ft_strcmp(argv[1], "env") == 0)
		out = env(envp);
	else if (ft_strcmp(argv[1], "pwd") == 0)
		out = pwd(envp);
	/*
	else if (ft_strcmp(argv[1], "unset") == 0)
		out = unset(envp);
	else if (ft_strcmp(argv[1], "export") == 0)
		out = export(envp);
	*/
	else if (ft_strcmp(argv[1], "exit") == 0)
		exit(0);
	return (out);
}

int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	return (built_ins(argv, envp));
}
