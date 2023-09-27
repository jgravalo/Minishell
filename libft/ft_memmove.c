/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:15 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:34:53 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if ((unsigned char *) dst == (unsigned char *) src)
		return (dst);
	if ((unsigned char *) dst < (unsigned char *) src)
	{
		while (i < n)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i++;
		}	
	}
	else
	{	
		i = n;
		while (i > 0)
		{
			((unsigned char *) dst)[i - 1] = ((unsigned char *) src)[i - 1];
			i--;
		}
	}
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
    char *src = "Hola tio";
    char dest[20];

    ft_memmove(dest, src, 9);
    //memset(str, 'A', 3);
    printf("%s", dest);
}
*/
