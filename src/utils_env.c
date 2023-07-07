#include "../inc/minishell.h"

int search_var_num(char *name, char **envp)
{
    int     i;
    int     j;

    i = 0;
    while (envp[i])
    {
        j = 0;
        while (name[j] && envp[i][j] == name[j])
            j++;
        if (!name[j])
            return (i);
        i++;
    }
    return (-1);
}

char *search_var(char *name, char **envp)
{
	int		env;
    char	*var;

    env = search_var_num(name, envp);
    var = ft_strchr(envp[env], '=') + 1;
	return (var);
}
