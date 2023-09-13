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

t_redir	*ft_redirlstnew(void *content, int type)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->path = content;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_redirlstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*curr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = ft_redirlstlast(*lst);
	curr->next = new;
}

t_redir	*ft_redirlstlast(t_redir *lst)
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