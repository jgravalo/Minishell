#include "../../inc/minishell.h"

static int is_it_numeric(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (is_digit(line[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void ft_exit(t_shell *shell)
{
	int argument;
	
	if (is_it_numeric(shell->args[1]) == 0)
	{
		write(2, "numeric argument required\n", 27);
		exit (255);
	}
	argument = ft_atoi(shell->args[1]);
	if (argument >= 0 && argument <= 255)
		exit (argument);
	else
		exit(156);
}