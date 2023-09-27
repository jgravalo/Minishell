/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:34:27 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/03 13:52:05 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
/*
#include <string.h>
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	c;

	c = 0;
	i = 0;
	while (src[c] != '\0')
		++c;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (c);
}
/*
int main(void) 
{
	char src[] = "Hello";
	char dest[] = "Goodbye";
	unsigned int size;

	size = 5;

	printf("%u \n", ft_strlcpy(dest, src, size));
	printf("%lu", strlcpy(dest, src, size));
}
*/
