/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:01 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/10 10:00:42 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static size_t	ft_strlen(const char *s)
{
	unsigned int	c;

	c = 0;
	while (*s)
	{
		c++;
		s++;
	}
	return (c);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;

	i = 0;
	while (s2[i] != '\0' && len)
	{
		if (s1[i] != s2[i])
			return (1);
	i++;
	len--;
	}
	if (s2[i] != '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{	
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
/*
#include <string.h>

int main(void)
{
	printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 0));
	//printf("%s", strnstr("lorem ipsum dolor sit amet", "dolor", 0));
	return (0);
}
*/