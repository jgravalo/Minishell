#include "../../inc/minishell.h"
/*
int	cd(char *rute, char **envp)
{
	int	*pwd;
	int	*oldpwd;

	if (rute[1] != '/')
		rute = ft_strjoin(search_var("PWD", envp), rute);
	pwd = search_var_num("PWD", envp);
	oldpwd = search_var_num("OLDPWD", envp);
	envp[oldpwd] = ft_strjoin("OLDPWD=", search_var("PWD", envp));
	envp[pwd] = ft_strjoin("PWD=", rute);
	return (0);
}
*/
int	cd(char *rute)
{
	int exit;

	exit = chdir(rute);
	/*
	if (exit < 0)
	{
		write(1, rute, ft_strlen(rute));
		write(1, ": no such file or directory\n", 28);
		exit (-1);
	}
	*/
	return (0);
}

int main(int argc, char **argv)//, char **envp)
{
	if (!argc)
		return (0);
	printf("rute = %s\n", argv[1]);
	cd(argv[1]);
	return (0);
}
