#include "../inc/minishell.h"

int search_varnum(char *name, char **envp)
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

    env = search_varnum(name, envp);
    var = ft_strchr(envp[env], '=') + 1;
	return (var);
}

void	check_vars(char *args, char **envp)
{
	int	i;
	int	start;
	char	*name;
	char	*env;

	i = 0;
	while (args[i])
	{
		if (args[i] == '$')
		{
			start = i;
			while ((args[i] > '0' && args[i] < '9') ||
				(args[i] > 'A' && args[i] < 'Z') ||
				(args[i] > 'a' && args[i] < 'z'))
			{
				i++;
			}
			name = ft_substr(args, start, i - start);
			env = search_var(name, envp);
//			args = change_var(args, name, env);
			free(name);
		}
		i++;
	}
}
