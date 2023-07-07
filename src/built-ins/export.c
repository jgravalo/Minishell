#include "../../inc/minishell.h"

int export_n(char *var, char ***envp)
{
	char	**new;
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	if (var[i] != '=')
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(*envp) + 2);
	i = 1;
	while (*envp[i])
	{
		new[i] = *envp[i];
		i++;
	}
	new[i] = var;
	*envp = new;
	return (0);
}

int export(char **argv, char ***envp)
{
    int i;

    i = 0;
    while (argv[i])
    {
        export_n(argv[i], envp);
        i++;
    }
    return (0);
}
