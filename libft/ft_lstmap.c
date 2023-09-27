/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:12:58 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/11 08:35:28 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

static t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

static t_list	*ft_lstlast(t_list *lst)
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

static void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

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

static void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if (*lst == NULL || del == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		del(curr->content);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr;
	t_list	*tmp;

	new = NULL;
	tmp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	curr = lst;
	while (curr != NULL)
	{	
		tmp = ft_lstnew(curr->content);
		if (!tmp)
		{	
			ft_lstclear(&new, del);
			return (NULL);
		}	
		tmp->content = f(tmp->content);
		ft_lstadd_back(&new, tmp);
		curr = curr->next;
	}
	return (new);
}

/*
int main(void)
{
	t_list *root;
	int a = 5;

	root = ft_lstnew(&a);
	t_list *elem2 = ft_lstnew(&a);
	ft_lstadd_back(&root, elem2);
	ft_lstmap(root, &ft_add_one);
}
*/