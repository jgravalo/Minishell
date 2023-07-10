# ifndef BUILTINS_H
# define BUILTINS_H


int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute, char **envp);

int unset(char **var, char ***envp);

int export(char **var, char ***envp);

int run_cd(char **args, char **envp);

int run_builtin(char **args, char **envp);

#endif
