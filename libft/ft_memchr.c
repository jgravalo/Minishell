/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:04:25 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/10 08:22:12 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n)
	{
		if (*ptr == (unsigned char) c)
			return ((unsigned char *) ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *src = "/|\x12\xff\x09\x42\2002\42|\\";
 	int size = 10;
   // printf("%p", ft_memchr(src, '\200', size));
	//printf("%p", memchr(src, '\200', size));
}
*/
