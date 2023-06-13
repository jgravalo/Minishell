#include <fcntl.h>
//# include <defines.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "gnl/get_next_line.h"

int	parse_line(char *line)
{
	char	**args;
	pid_t	pid;

	args = ft_split(line, ' ');
	pid = fork();
	if (pid == 0)

	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char *c;

	if (!argc && !argv && !envp)
		return (0);
	while (1)
	{
		write(1, "jgravalo>", 9);
		c = get_next_line(0);
//		c = readline(NULL);
		printf("%s", c);
		parse_line(c);
	}
	 return (0);
}
