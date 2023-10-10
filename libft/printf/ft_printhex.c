/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:30:53 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/10 09:01:00 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	ft_num_len(unsigned long number)
{
	size_t	len;

	len = 1;
	while (number / 16)
	{
		number /= 16;
		len++;
	}
	return (len);
}

static char	*ft_create_arr(char *str, unsigned long number,
			size_t len, char *base)
{
	str[len] = '\0';
	if (number == 0)
		str[len - 1] = '0';
	while (number > 0)
	{
		str[len - 1] = base[number % 16];
		number /= 16;
		len--;
	}
	return (str);
}

size_t	ft_printhex(int fd, unsigned int n, char *base)
{
	unsigned long	number;
	size_t			count;	
	size_t			len;
	char			*str;

	count = 0;
	number = (unsigned long ) n;
	len = ft_num_len(number);
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (!str)
		return (-1);
	ft_create_arr(str, number, len, base);
	count = ft_printstr(fd, str);
	if ((int) count == -1)
	{
		free (str);
		return (-1);
	}
	free (str);
	str = NULL;
	return (count);
}
