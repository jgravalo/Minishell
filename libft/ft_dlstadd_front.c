/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:15:03 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/22 18:25:36 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{	
	if (lst)
	{
		if (!new)
			return ;
		if (*lst == NULL)
		{
			*lst = new;
			new->prev = NULL;
			new->next = NULL;
		}
		else
		{
			new->next = *lst;
			new->prev = NULL;
			*lst = new;
		}
	}
}
