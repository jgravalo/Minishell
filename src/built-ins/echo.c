#include "../../inc/minishell.h"

int	echo(char **argv)
{
	int		i;
	i = 1;
	while (argv && argv[i])
	{
		if (!(i == 1 && ft_strcmp(argv[i], "-n") == 0))
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-n") != 0))
		write(1, "\n", 1);
	return (0);
}
