/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:06:10 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:34:21 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{	
	if (n == 0)
		return (0);
	while (n)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *) s1 - *(unsigned char *) s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{ 
		char str[] = "Heaa";
		char str_1[] = "Heuu";
		
		int arr1[] = {1,2};
		int arr2[] = {1,3};

		printf("%d",ft_memcmp(arr1,arr2, 2 * sizeof (int)));

}
*/
