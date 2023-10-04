/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:01:43 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/09 12:04:40 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*

#include <stdio.h>
int main(void)
{ 
    char *src = "Hola tio";
    char dest[20];
	
	int arr1[] = {678, 790};
	int arr2[] = {2345, 2346};
    ft_memcpy(arr1, arr2, 2 * sizeof (int));
    //memset(str, 'A', 3);
    printf("%d %d", arr1[0], arr1[1]);
}
*/