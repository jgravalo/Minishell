#include "../../inc/minishell.h"

int unset_n(char *var, char ***envp)
{
	char	**new;
	int		i;
	int		j;
	int		n;

	printf("var = |%s|\n", var);
//	check_errors();
	n = search_var_num(var, *envp);
	if (n < 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(*envp));
	i = 1;
	j = 0;
	env(*envp);
	while (*envp[i + j])
	{
		if (i == n)
		{
			free(*envp[i]);
			j++;
		}
		printf("aqui\n");
		printf("envp = %s\n", *envp[i + j]);
		new[i] = *envp[i + j];
		i++;
	}
	env(*envp);
	*envp = new;
	return (0);
}

int unset(char **argv, char ***envp)
{
	int i;

	i = 1;
	while (argv[i])
	{
		unset_n(argv[i], envp);
		i++;
	}
	return (0);
}
