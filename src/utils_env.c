#include "../inc/minishell.h"

int search_var(char *name, char **envp)
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
//		printf("%d, ", i);
        i++;
    }
    return (-1);
}
