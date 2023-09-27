/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:15:24 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/22 13:05:21 by theonewhokn      ###   ########.fr       */
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