#include "../../inc/minishell.h"

void	make_history(t_hist *hist, char *line)
{
	t_hist	*new;

	new = (t_hist *)malloc(sizeof(t_hist));
	if (hist == NULL)
	{
		new->line = line;
		new->next = NULL;
		new->ant = NULL;
	}
	else
	{
		/*
	write(1, "line = \"", 8);
	write(1, line, ft_strlen(line));
	write(1, "\"\n", 2);
	*/
		new->line = line;
		new->next = hist;
		new->ant = NULL;
		hist = new;
	write(1, "line = \"", 8);
	write(1, new->line, ft_strlen(new->line));
	write(1, hist->next->line, ft_strlen(hist->next->line));
	write(1, "\"\n", 2);
	}
}

void	print_history(t_hist *hist)
{
	t_hist	*ptr;

	ptr = hist;
	while (ptr != NULL)
	{
		write(1, ptr->line, ft_strlen(ptr->line));
		ptr = ptr->next;
	}
}

void	free_history(t_hist *lst)
{
	t_hist	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = ptr->next;
		free(ptr);
	}
	free(lst);
}
