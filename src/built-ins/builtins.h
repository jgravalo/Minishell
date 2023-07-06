# ifndef BUILTINS_H
# define BUILTINS_H


int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute, char **envp);

#endif
