/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:12:58 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/28 09:34:20 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
