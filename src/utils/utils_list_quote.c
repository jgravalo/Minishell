#include "../../inc/minishell.h"

t_quote	*ft_quotelstnew(int start, int end)
{
	t_quote	*node;

	node = (t_quote *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->start = start;
	node->end = end;
	node->next = NULL;
	return (node);
}

void	ft_quotelstadd_back(t_quote **lst, t_quote *new)
{
	t_quote	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = ft_quotelstlast(*lst);
	curr->next = new;
}

t_quote	*ft_quotelstlast(t_quote *lst)
{
	if (!lst)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}


