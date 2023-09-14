#include "../inc/minishell.h"

void	set_argv(t_cmd **cmd)
{
	int i;
	int	j;
	t_arg	*ptr;

	i = 0;
	j = 0;
	while (cmd[i])
	{	
		cmd[i]->args = malloc(sizeof (char * ) * ft_arglstsize(cmd[i]->arg) + 1);
		ptr = cmd[i]->arg;
		while(ptr)
		{
			cmd[i]->args[j++] = ft_strdup(ptr->arg);
			ptr = ptr->next;
		}
		i++;
		j = 0;
	}
}