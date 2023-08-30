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

void ft_exit(t_shell *shell, int n)
{	
	int64_t argument;
	uint64_t u_argument;

	if (shell->struct_cmd[n]->args[1] != NULL)
	{
		argument = ft_atoi(shell->struct_cmd[n]->args[1]);
		if (shell->struct_cmd[n]->args[1][0] != '-')
		{	
			u_argument = ft_u_atoi(shell->struct_cmd[n]->args[1]);
			if (u_argument > LONG_MAX)
			{
				write(2, "exit\n", 6);
				write(2, "bash: exit: numeric argument required\n", 39);
				exit(2);
			}
		}
		if (argument < LONG_MIN || is_it_numeric(shell->struct_cmd[n]->args[1]) == 0)
		{	
			write(2, "exit\n", 6);
			write(2, "bash: exit: numeric argument required\n", 39);
			exit(2);
		}
		else if (shell->struct_cmd[n]->args[2] != NULL)
		{	
			write(2, "exit", 5);
			write(2, "bash: exit: too many arguments\n", 32);
			exit(1);
		}
		exit(argument);
	}
	else
		exit(shell->exit);

}