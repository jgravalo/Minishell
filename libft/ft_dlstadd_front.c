/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:15:03 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/28 09:35:00 by dtome-pe         ###   ########.fr       */
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
