/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:15:24 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/28 09:35:05 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_dlstadd_back(t_dlist **head, t_dlist **tail, t_dlist *new)
{
	t_dlist	*curr;

	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
		return ;
	}
	curr = *head;
	curr = ft_dlstlast(curr);
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
	*tail = new;
}
/*
int main(void)
{   
   
    
}

*/