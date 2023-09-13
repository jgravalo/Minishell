#include "../inc/minishell.h"

t_tok	*ft_lstnew(void *content)
{
	t_tok	*node;

	node = (t_tok *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->token = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = ft_lstlast(*lst);
	curr->next = new;
}

t_tok	*ft_lstlast(t_tok *lst)
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

void	ft_printlst(t_tok *lst)
{
	while (lst)
	{
		printf("%s\n", lst->token);
		lst = lst->next;
	}
}

void	ft_printbothlst(t_tok *lst)
{
	while (lst)
	{
		printf("%s\n", lst->token);
		printf("%s\n", lst->type);
		lst = lst->next;
	}
}