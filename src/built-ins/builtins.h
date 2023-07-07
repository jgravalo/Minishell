# ifndef BUILTINS_H
# define BUILTINS_H


int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute, char **envp);

int unset(char *var, char ***envp);

int export(char *var, char ***envp);

#endif
