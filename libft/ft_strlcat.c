/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:34:10 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/09 13:54:33 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	j = 0;
	i = 0;
	if (dstsize <= dlen)
		return (slen + dstsize);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < (dstsize - dlen - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dlen + slen);
}
/*
int main(void)
{
		char *src = "lorem ipsum dolor sit amet";
		char dest[10] = "a";
		//printf("%zu\n", strlcat(dest, "lorem ipsum dolor sit amet", 6));
		//write(1, "\n", 1);
		//write(1, dest, 15);

		printf("%zu\n", ft_strlcat(dest, src, 1));
		write(1, "\n", 1);
		write(1, dest, 1);
		//ft_putstr(dest);


}
*/