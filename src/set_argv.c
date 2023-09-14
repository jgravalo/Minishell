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
		ptr = cmd[i]->argx;
		cmd[i]->args = malloc(sizeof (char * ) * (ft_arglstsize(ptr) + 1));
		while(ptr)
		{	
			cmd[i]->args[j] = ft_strdup(ptr->arg);
			j++;
			ptr = ptr->next;
		}
		cmd[i]->args[j] = NULL;
		i++;
		j = 0;
	}
}