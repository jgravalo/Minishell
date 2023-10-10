/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:27:07 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/10 09:01:42 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static size_t	ft_num_len(unsigned long number)
{
	size_t	len;

	len = 1;
	while (number / 10)
	{
		number /= 10;
		len++;
	}
	return (len);
}

static char	*ft_create_str(char *str, size_t len, unsigned long number)
{
	str[len] = '\0';
	if (number == 0)
		str[len - 1] = '0';
	while (number > 0)
	{
		str[len - 1] = number % 10 + '0';
		number /= 10;
		len--;
	}
	return (str);
}

size_t	ft_printunbr(int fd, unsigned int n)
{
	unsigned long	number;
	size_t			count;
	size_t			len;
	char			*str;

	count = 0;
	number = (unsigned long) n;
	len = ft_num_len(number);
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (!str)
		return (-1);
	ft_create_str(str, len, number);
	count = ft_printstr(fd, str);
	if ((int) count == -1)
	{
		free (str);
		str = NULL;
		return (-1);
	}
	free (str);
	str = NULL;
	return (count);
}
