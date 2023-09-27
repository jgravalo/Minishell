/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:12:28 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/23 11:14:29 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*node;

	node = (t_dlist *)malloc(sizeof (*node));
	if (!node)
		return (NULL);
	node->content = content;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
/*
int main(void)
{   
    t_list *node;
    int x;

    x = 5;
    node = ft_lstnew(&x);
    printf("node content is %d", *(int *)(node->content));
    free (node);
    
}
*/
