# include "../../inc/minishell.h"

int	cd(char *rute, char **envp)
{
	int		out;
	char	*tmp;
	int pwd;
	int oldpwd;
	char	buffer[100];

	if (!envp)
		return (0);
	if (rute == NULL) // cd a HOME
		rute = search_var("HOME", envp);
	else if (rute[0] != '/' && ft_strcmp(rute, "..") != 0)
	{
		tmp = ft_strjoin(search_var("PWD", envp), "/");
		rute = ft_strjoin(tmp, rute);
		free(tmp);
	}
	/*
	oldpwd = search_var_num("OLDPWD", envp);
	envp[oldpwd] = ft_strjoin("OLDPWD=", search_var("PWD", envp));
	pwd = search_var_num("PWD", envp);
	envp[pwd] = ft_strjoin("PWD=", rute);
	*/

	printf("%s\n", getcwd(buffer, 100));
	oldpwd = search_var_num("OLDPWD", envp);
	envp[oldpwd] = ft_strjoin("OLDPWD=", getcwd(buffer, 100));
	out	= chdir(rute);
	if (out < 0)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, rute, ft_strlen(rute));
		write(1, "\n", 1);
		return (1);
	}
	pwd = search_var_num("PWD", envp);
	envp[pwd] = ft_strjoin("PWD=", getcwd(buffer, 100));
	printf("%s\n", getcwd(buffer, 100));
	return (0);
}
