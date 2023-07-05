#include "../../inc/minishell.h"

int	cd(char *rute)
{
	int out;

	
	if (rute[1] != '/')
		rute = ft_strjoin(search_var("PWD", envp), rute);
	pwd = search_var_num("PWD", envp);
	oldpwd = search_var_num("OLDPWD", envp);
	envp[oldpwd] = ft_strjoin("OLDPWD=", search_var("PWD", envp));
	envp[pwd] = ft_strjoin("PWD=", rute);
	
	out	= chdir(rute);
	if (out < 0)
	{
		write(1, rute, ft_strlen(rute));
		write(1, ": no such file or directory\n", 28);
		exit (-1);
	}
	return (0);
}
