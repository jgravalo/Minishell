# ifndef BUILTINS_H
# define BUILTINS_H
# include "../../inc/minishell.h"


int	env(char **envp);

int	pwd(char **envp);

int	echo(char **argv);

int	cd(char *rute);

#endif
