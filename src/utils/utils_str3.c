/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:17:40 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 10:07:39 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

int	words(const char *s, char c)
{
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
			{
				s++;
			}
			j++;
		}
		else
			++s;
	}
	return (j);
}

void	move_ptrs(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

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
